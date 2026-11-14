/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Low level driver implementation for SoC FPGA USB3.1 XHCI controller.
 * Commands sub-module.
 */

#include "xhci_commands.h"
#include "xhci_doorbell.h"
#include "xhci_port.h"

xhci_trb_t *xhci_get_cmdring_enq_ptr(xcr_command_ring_t *cmd_ring)
{
    xhci_trb_t *enq_ptr = cmd_ring->xcr_enqueue_ptr;
    if ((enq_ptr == NULL) || (cmd_ring == NULL))
    {
        return NULL;
    }
    volatile uint32_t c_bit;

    while (true)
    {
        if (xhci_is_link_trb(enq_ptr) == 1)
        {
            enq_ptr = xhci_get_next_trb_segment(enq_ptr, &cmd_ring->xcr_ccs_flag);
        }
        c_bit = (enq_ptr->control & 0x00000001U);
        if (c_bit == cmd_ring->xcr_ccs_flag)
        {
            enq_ptr = enq_ptr + 1;
        }
        else
        {
            break;
        }
    }

    return enq_ptr;
}

void xhci_set_device_address(struct xhci_data *xhci_ptr)
{
    uint32_t cmd_ctrl_flags;
    xhci_trb_t *enq_ptr;

    enq_ptr = xhci_get_cmdring_enq_ptr(xhci_ptr->xcr_ring);
    if (enq_ptr == NULL)
    {
        return;
    }

    enq_ptr->buffer = (uint64_t)xhci_ptr->ip_ctx;

    cmd_ctrl_flags = (1 << SLOT_ID_FIELD);
    cmd_ctrl_flags |= (ADDRESS_DEVICE_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xhci_ptr->xcr_ring->xcr_ccs_flag;
    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xhci_ptr->xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}

void xhci_reset_command_ring(xcr_command_ring_t *xcr_ring)
{
    uint32_t crcr_reg;
    uint32_t crcr_addr;

    /* first stop the command ring operation */
    crcr_reg = RD_REG32((XHCI_BASE_ADDR + USB3_CRCR_LO));
    crcr_reg |= (0x2U);
    WR_REG32((XHCI_BASE_ADDR + USB3_CRCR_LO), crcr_reg);

    crcr_addr = ((uint32_t)(uintptr_t) (&xcr_ring->xcr_dequeue_ptr) &
            0xffffffffU);
    WR_REG32((XHCI_BASE_ADDR + USB3_CRCR_LO), crcr_addr);
}

void xhci_enable_slot_command(xcr_command_ring_t *xcr_ring)
{
    xhci_trb_t *enq_ptr;
    uint32_t cmd_ctrl_flags;

    enq_ptr = xhci_get_cmdring_enq_ptr(xcr_ring);
    if (enq_ptr == NULL)
    {
        return;
    }

    cmd_ctrl_flags = ((uint32_t) ENABLE_SLOT_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xcr_ring->xcr_ccs_flag;

    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    /* call doorbell register */
    ring_xhci_host_db();

}
void xhci_disable_slot_command(xcr_command_ring_t *xcr_ring, uint32_t slotid)
{
    xhci_trb_t *enq_ptr;
    uint32_t cmd_ctrl_flags;

    enq_ptr = xhci_get_cmdring_enq_ptr(xcr_ring);
    if (enq_ptr == NULL)
    {
        return;
    }

    cmd_ctrl_flags = ((uint32_t) DISABLE_SLOT_CMD << TRB_FIELD);
    cmd_ctrl_flags |= (slotid << SLOTID_FIELD);
    cmd_ctrl_flags |= xcr_ring->xcr_ccs_flag;

    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    /* call doorbell register */
    ring_xhci_host_db();
}

void xhci_configure_endpoint(struct xhci_data *xhci_ptr)
{
    uint32_t cmd_ctrl_flags;
    xhci_trb_t *enq_ptr;

    enq_ptr = xhci_get_cmdring_enq_ptr(xhci_ptr->xcr_ring);
    if ((enq_ptr == NULL) || (xhci_ptr == NULL))
    {
        return;
    }

    enq_ptr->buffer = (uint64_t)xhci_ptr->ip_ctx;
    enq_ptr->status = 0U;

    cmd_ctrl_flags = 0;
    cmd_ctrl_flags |= ((uint32_t) 1 << SLOT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) CONFIGURE_ENDPOINT_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xhci_ptr->xcr_ring->xcr_ccs_flag;

    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xhci_ptr->xcr_ring->xcr_enqueue_ptr,
            XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}

static void stop_endpoint_command(xcr_command_ring_t *xcr_ring)
{
    uint32_t cmd_ctrl_flags;
    xhci_trb_t *enq_ptr;

    enq_ptr = xhci_get_cmdring_enq_ptr(xcr_ring);
    if (enq_ptr == NULL)
    {
        return;
    }

    enq_ptr->buffer = 0U;
    enq_ptr->status = 0U;

    cmd_ctrl_flags = 0;
    cmd_ctrl_flags |= ((uint32_t) 1U << SLOT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) 1U << SP_BIT_FIELD);
    cmd_ctrl_flags |= ((uint32_t) 1U << ENDPOINT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) STOP_ENDPOINT_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xcr_ring->xcr_ccs_flag;

    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}

void xhci_update_ep_transfer_ring(xcr_command_ring_t *xcr_ring, xhci_trb_t *xtr_ring)
{
    uint32_t cmd_ctrl_flags;
    xhci_trb_t *enq_ptr;
    if (xtr_ring == NULL)
    {
        return;
    }
    /*
     * first stop the endpoint using stop endpoint command xhci_trb_t
     * Then update the TR pointer
     */
    stop_endpoint_command(xcr_ring);

    enq_ptr = xhci_get_cmdring_enq_ptr(xcr_ring);

    enq_ptr->buffer = (uint64_t)xtr_ring;
    enq_ptr->status = 0U;

    cmd_ctrl_flags = 0;
    cmd_ctrl_flags |= ((uint32_t) 1U << SLOT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) 1U << ENDPOINT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) SET_TR_DEQUEUE_PTR_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xcr_ring->xcr_ccs_flag;

    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}

void xhci_evaluate_endpoint(struct xhci_data *xhci_ptr)
{
    uint32_t cmd_ctrl_flags = 0U;
    const uint8_t slotid = xhci_ptr->dev_data.slot_id;
    xhci_trb_t *enq_ptr;

    if (xhci_ptr == NULL)
    {
        return;
    }

    enq_ptr = xhci_get_cmdring_enq_ptr(xhci_ptr->xcr_ring);

    enq_ptr->buffer = (uint64_t)xhci_ptr->ip_ctx;
    enq_ptr->status = 0U;

    cmd_ctrl_flags |= ((uint32_t) slotid << SLOT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) EVALUATE_CONTEXT_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xhci_ptr->xcr_ring->xcr_ccs_flag;
    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xhci_ptr->xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}

void xhci_reset_endpoint_command(xcr_command_ring_t *xcr_ring, uint8_t slot_id, uint8_t dci)
{
    uint32_t cmd_ctrl_flags = 0U;
    xhci_trb_t *enq_ptr = xhci_get_cmdring_enq_ptr(xcr_ring);

    if (enq_ptr == NULL)
    {
        return;
    }

    enq_ptr->buffer = 0U;
    enq_ptr->status = 0U;

    /* TSP = 0: reset the data toggle / sequence number as well */
    cmd_ctrl_flags |= ((uint32_t) slot_id << SLOT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) dci << ENDPOINT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) RESET_ENDPOINT_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xcr_ring->xcr_ccs_flag;
    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}

void xhci_set_tr_dequeue_command(xcr_command_ring_t *xcr_ring, uint8_t slot_id, uint8_t dci,
        xhci_trb_t *deq_ptr, uint8_t dcs)
{
    uint32_t cmd_ctrl_flags = 0U;
    xhci_trb_t *enq_ptr = xhci_get_cmdring_enq_ptr(xcr_ring);

    if ((enq_ptr == NULL) || (deq_ptr == NULL))
    {
        return;
    }

    /* bit 0: DCS, bits 3:1 SCT = 0 (primary transfer ring) */
    enq_ptr->buffer = ((uint64_t)(uintptr_t) deq_ptr) | (uint64_t)(dcs & 0x1U);
    enq_ptr->status = 0U;

    cmd_ctrl_flags |= ((uint32_t) slot_id << SLOT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) dci << ENDPOINT_ID_FIELD);
    cmd_ctrl_flags |= ((uint32_t) SET_TR_DEQUEUE_PTR_CMD << TRB_FIELD);
    cmd_ctrl_flags |= xcr_ring->xcr_ccs_flag;
    enq_ptr->control = cmd_ctrl_flags;

    xhci_dcache_clean((void *) xcr_ring->xcr_enqueue_ptr,
            (size_t) XHCI_CR_TRB_LEN * sizeof(xhci_trb_t));

    ring_xhci_host_db();
}
