/*
 * SPDX-FileCopyrightText: Copyright (C) 2025-2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Low level driver implementation for SoC FPGA USB3.1 XHCI controller.
 * Rings sub-module.
 */

#include <stdlib.h>
#include "host/hcd.h"
#include "osal_log.h"
#include "xhci.h"

#define XHCI_REG_BASE (0x11000000)

/*************************************************************************************************/
/*                                  xHCI Rings                                                   */
/*************************************************************************************************/
/*
 * xHCI rings are implemented with the help of TRB ( Transfer Request Block ). A TRB is the
 * basic data storage unit of the xhci controller. TRB is owned either by the producer/consumer.
 * The producer is responsible for creating a TRB, while consumer is responsible for the
 * consumption of the trb.
 *
 *  xHCI rings are classified as :
 *
 *       -> Command Ring
 *              Command ring is used to send any xHCI specific commands to the controller. Here, the
 *              SW is the producer and xHCI is the consumer.
 *       -> Event Ring
 *              xHCI reports the status of all the events via the event ring. SW is the consumer of
 *              this ring.
 *       -> Transfer Ring
 *              Transfer rings are associated with endpoints to carry out transfers.
 */

int xhci_crcr_init(xcr_command_ring_t *xcr_ring)
{
    volatile xhci_regs_t *xhci = (volatile xhci_regs_t *)(uintptr_t) XHCI_REG_BASE;

    int ret;

    xcr_ring->xcr_dequeue_ptr = allocate_ring_segment(64, XHCI_CR_TRB_LEN);
    if (xcr_ring->xcr_dequeue_ptr == NULL)
    {
        return -ENOMEM;
    }

    /* memory alignment check */
    ret = is_ptr_mem_aligned((uint64_t)xcr_ring->xcr_dequeue_ptr, 64U);
    if (ret != 0)
    {
        if (xcr_ring->xcr_dequeue_ptr != NULL)
        {
            vPortFree(xcr_ring->xcr_dequeue_ptr);
        }
        return ret;
    }

    xcr_ring->xcr_enqueue_ptr = xcr_ring->xcr_dequeue_ptr;
    xcr_ring->xcr_ccs_flag = XHCI_CR_CCS_FLAG;

    xhci->crcr_lo.value =
            (((uint32_t)(uintptr_t)xcr_ring->xcr_dequeue_ptr) &
             USB3_CRCR_LO_CMD_RING_PNTR_MASK) |
            (uint32_t) xcr_ring->xcr_ccs_flag;
    xhci->crcr_hi.value = (uint32_t)((uintptr_t) xcr_ring->xcr_dequeue_ptr >> 32);

    return 0;
}

int init_xhc_event_ring(struct xhci_data *xhci_ptr)
{
    int ret;
    uint64_t ring_addr;
    uint64_t erdp_reg_val;
    uint64_t rt_base_addr;

    volatile xhci_runtime_regs_t *runtime;
    xer_event_ring_t *xer_ring;

    xer_ring = &xhci_ptr->xer_ring;

    rt_base_addr = xhci_ptr->op_regs.xhci_runtime_base;
    runtime = (volatile xhci_runtime_regs_t *)(uintptr_t) rt_base_addr;

    runtime->erstsz.value =
            (runtime->erstsz.value & ~(USB3_ERSTSZ_ERS_TABLE_SIZE_MASK)) |
            XHCI_EVENT_RING_TABLE_SZ;

    xer_ring->erst_ptr = (xhci_erst_entry_t *)(uintptr_t) pvPortAlignedAlloc(64,
            1U * sizeof(xhci_erst_entry_t));
    if (xer_ring->erst_ptr == NULL)
    {
        ERROR("Canot allocate memory!!!");
        return -ENOMEM;
    }

    ret = is_ptr_mem_aligned((uint64_t)xer_ring->erst_ptr, 64U);
    if (ret != 0)
    {
        ERROR("Memory alignment error!!!");
        if (xer_ring->erst_ptr != NULL)
        {
            vPortFree(xer_ring->erst_ptr);
        }
        return ret;
    }

    bzero(xer_ring->erst_ptr, sizeof(xhci_erst_entry_t));

    xer_ring->xer_enqueue_ptr = (xhci_trb_t *)(uintptr_t) pvPortAlignedAlloc(64,
            XHCI_EVENT_RING_SEG_LENGTH * sizeof(xhci_trb_t));

    if (xer_ring->xer_enqueue_ptr == NULL)
    {
        ERROR("Canot allocate memory!!!");
        return -ENOMEM;
    }

    /* memory alignment check */
    ret = is_ptr_mem_aligned((uint64_t)xer_ring->xer_enqueue_ptr, 64U);
    if (ret != 0)
    {
        ERROR("Memory alignment error!!!");
        if (xer_ring->xer_enqueue_ptr != NULL)
        {
            vPortFree(xer_ring->xer_enqueue_ptr);
        }
        return ret;
    }
    bzero(xer_ring->xer_enqueue_ptr,
            XHCI_EVENT_RING_SEG_LENGTH * sizeof(xhci_trb_t));

    xer_ring->trb_count = XHCI_EVENT_RING_SEG_LENGTH;

    xer_ring->erst_ptr->seg_addr = (uint64_t)xer_ring->xer_enqueue_ptr;
    /* number of trbs in the segment */
    xer_ring->erst_ptr->seg_size = XHCI_EVENT_RING_SEG_LENGTH;
    xer_ring->erst_ptr->rsvd = 0U;

    ring_addr = (uint64_t)xer_ring->erst_ptr;
    runtime->erstba_lo.value =
            (uint32_t) (ring_addr & ~(0x3fUL));
    runtime->erstba_hi.value = (uint32_t) (ring_addr >> 32);

    ring_addr = (uint64_t) (xer_ring->xer_enqueue_ptr);
    erdp_reg_val = runtime->erdp_lo.value &
            ~(uint64_t) USB3_ERDP_LO_ERD_PNTR_MASK;
    erdp_reg_val |= ring_addr;
    runtime->erdp_lo.value = (uint32_t) erdp_reg_val;
    runtime->erdp_hi.value = (uint32_t) (ring_addr >> 32);

    hcd_dcache_clean(xer_ring->erst_ptr,
            sizeof(xhci_erst_entry_t));
    hcd_dcache_clean(xer_ring->xer_enqueue_ptr,
            XHCI_EVENT_RING_SEG_LENGTH * sizeof(xhci_trb_t));

    TU_LOG3("Event Ring configured successfully");
    return 0;
}

xhci_trb_t *allocate_ring_segment(int req_byte_align, int req_trb_len)
{
    int ret;
    xhci_trb_t *xtr = NULL;
    xhci_trb_t *link_trb;
    uint32_t ring_ctrl_flags = 0U;

    xtr = (xhci_trb_t *)pvPortAlignedAlloc(req_byte_align,
            (size_t)req_trb_len * sizeof(xhci_trb_t));
    if (xtr == NULL)
    {
        ERROR("Cannot allocate memory!!!");
        return NULL;
    }

    bzero(xtr, (size_t)req_trb_len * sizeof(xhci_trb_t));

    /* memory alignment check */
    ret = is_ptr_mem_aligned((uint64_t)xtr, (uint32_t)req_byte_align);
    if (ret != 0)
    {
        ERROR("Memory alignment error!!!");
        if (xtr != NULL)
        {
            vPortFree(xtr);
        }
        return NULL;
    }

    link_trb = xtr + req_trb_len - 1;

    /* link trb points to the first trb of the ring */
    link_trb->buffer = (uint64_t)(uintptr_t)xtr;
    link_trb->status = 0U;

    ring_ctrl_flags |= (1U << 1);
    ring_ctrl_flags |= ((uint32_t) LINK_TRB << 10);
    link_trb->control = ring_ctrl_flags;

    hcd_dcache_clean(xtr, (uint32_t) req_trb_len * sizeof(xhci_trb_t));

    return xtr;
}

xcr_command_ring_t *alloc_command_ring(void)
{
    xcr_command_ring_t *xcr_ring;
    xcr_ring = (xcr_command_ring_t *)malloc(sizeof(xcr_command_ring_t));
    if (xcr_ring == NULL)
    {
        ERROR("Canot allocate memory!!!");
        return NULL;
    }
    return xcr_ring;
}

int is_link_trb(xhci_trb_t *ptr)
{
    uint32_t trb_id;

    trb_id = (ptr->control & 0xfc00U) >> 10;

    if (trb_id == LINK_TRB)
    {
        return 1;
    }

    return 0;
}

xhci_trb_t *get_next_trb_segment(xhci_trb_t *ptr, uint8_t *pcs_flag)
{
    uint32_t link_ctrl = 0U;
    xhci_trb_t *next_seg_trb_ptr = NULL;

    xhci_trb_t *link_trb = ptr;

    link_ctrl = link_trb->control;
    link_ctrl &= ~(0x00000001U);
    link_ctrl |= (*pcs_flag);

    link_trb->control = link_ctrl;
    hcd_dcache_clean(link_trb, sizeof(xhci_trb_t));

    if ((link_trb->control & 0x00000002U) != 0U)
    {
        if (*pcs_flag != 0U)
        {
            *pcs_flag = 0U;
        }
        else
        {
            *pcs_flag = 1U;
        }
    }
    next_seg_trb_ptr = (xhci_trb_t *)link_trb->buffer;

    return next_seg_trb_ptr;
}
