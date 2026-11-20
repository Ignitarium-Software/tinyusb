/*
 * SPDX-FileCopyrightText: Copyright (C) 2025-2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Low level driver implementation for SoC FPGA USB3.1 XHCI controller.
 * Events sub-module
 */

#include <stdio.h>
#include "xhci_events.h"
#include "host/hcd.h"

static void erdp_register_update(xer_event_ring_t *xer_ring,
        volatile xhci_runtime_regs_t *runtime);

void display_event_trbs(struct xhci_data *xhci)
{
    hcd_dcache_invalidate(xhci->xer_ring.xer_enqueue_ptr,
            (size_t) (XHCI_EVENT_RING_SEG_LENGTH * sizeof(xhci_trb_t)));
    for (int i = 0; i < 10; i++)
    {
        TU_LOG3(" ID --> %d", i);
        TU_LOG3(" Address : %p", &xhci->xer_ring.xer_enqueue_ptr[i]);
        TU_LOG3(" Buffer : %lx", xhci->xer_ring.xer_enqueue_ptr[i].buffer);
        TU_LOG3(" Status : %x", xhci->xer_ring.xer_enqueue_ptr[i].status);
        TU_LOG3(" Control : %x", xhci->xer_ring.xer_enqueue_ptr[i].control);
        TU_LOG3(" TRB Value is : %d",
                ((xhci->xer_ring.xer_enqueue_ptr[i].control) & 0xfc00U) >> 10);
    }
}

uint8_t get_xhc_port_speed(uint8_t rhport)
{
    xhci_oper_reg_params_t op_reg = get_xhci_op_registers();
    volatile xhci_portsc_20_t *portsc =
            (volatile xhci_portsc_20_t *)(uintptr_t)
            (op_reg.xhci_op_base + PORTSC_REG_OFFSET +
             (0x10U * ((uint64_t) rhport - 1UL)));

    return (uint8_t) ((portsc->value & USB3_PORTSC_20_PORTSPEED_MASK) >>
            USB3_PORTSC_20_PORTSPEED_POS);
}

/*
 * @note : Bit 0 of PORTSC register returns the device connect/disconnect
 * status
 */
bool xhci_port_status(uint8_t rhport)
{
    xhci_oper_reg_params_t op_reg = get_xhci_op_registers();
    volatile xhci_portsc_20_t *portsc =
            (volatile xhci_portsc_20_t *)(uintptr_t)
            (op_reg.xhci_op_base + PORTSC_REG_OFFSET +
             (0x10U * ((uint64_t) rhport - 1UL)));

    /*Bit 0 gives attach/detach status */
    if ((portsc->value & USB3_PORTSC_20_CCS_MASK) != 0U)
    {
        return true;
    }
    return false;
}

/* reset the RH port */
void reset_xhci_port(uint8_t rhport)
{
    xhci_oper_reg_params_t op_reg = get_xhci_op_registers();
    volatile xhci_portsc_20_t *portsc =
            (volatile xhci_portsc_20_t *)(uintptr_t)
            (op_reg.xhci_op_base + PORTSC_REG_OFFSET +
             (0x10U * ((uint64_t) rhport - 1UL)));

    portsc->value |= USB3_PORTSC_20_PR_MASK;
    TU_LOG3("xHCI port reset initiated on port : %d", rhport);
}

bool is_xhci_port_reset_end(uint8_t rhport)
{
    volatile xhci_portsc_20_t *portsc;
    uint32_t loop = 100U;

    xhci_oper_reg_params_t op_reg = get_xhci_op_registers();
    portsc = (volatile xhci_portsc_20_t *)(uintptr_t)
            (op_reg.xhci_op_base + PORTSC_REG_OFFSET +
             (0x10U * ((uint64_t) rhport - 1UL)));
    do
    {
        if ((portsc->value & USB3_PORTSC_20_PR_MASK) == 0U)
        {
            break;
        }

        loop--;
        osal_task_delay(10);
    }while(loop > 0U);

    if (loop == 0U)
    {
        TU_LOG1("usb3 port reset failure");
        return false;
    }

    TU_LOG3("xHCI port reset completede on port : %d", rhport);
    return true;
}

xhci_event_trb_t get_xhc_event(struct xhci_data *xhci_ptr)
{
    uint64_t erdp_addr;
    volatile xhci_runtime_regs_t *runtime;
    xhci_event_trb_type_t trb_id;
    xhci_event_trb_t event = {0};

    /* decrement the event ring trb count */
    xhci_ptr->xer_ring.trb_count -= 1U;

    runtime = (volatile xhci_runtime_regs_t *)(uintptr_t)
            xhci_ptr->op_regs.xhci_runtime_base;
    erdp_addr = ((uint64_t) runtime->erdp_hi.value << 32) |
            runtime->erdp_lo.value;
    erdp_addr &= 0xfffffff0UL;

    hcd_dcache_invalidate((void *) erdp_addr, sizeof(xhci_trb_t));

    xhci_trb_t *event_trb = (xhci_trb_t *)(uint64_t)erdp_addr;

    trb_id = (xhci_event_trb_type_t)((event_trb->control & 0xfc00U) >> 10);

    if (trb_id == TRANSFER_EVENT)
    {
        event.tr_event.tr_trb_ptr = event_trb->buffer;
        event.tr_event.status_field = event_trb->status;
        event.tr_event.control_field = event_trb->control;
    }
    else if (trb_id == COMMAND_COMPLETION_EVENT)
    {
        event.cc_event.cmd_trb_ptr = event_trb->buffer;
        event.cc_event.status_field = event_trb->status;
        event.cc_event.control_field = event_trb->control;
    }
    else if (trb_id == PORT_STATUS_CHANGE_EVENT)
    {
        event.psc_event.buf = event_trb->buffer;
        event.psc_event.status_field = event_trb->status;
        event.psc_event.control_field = event_trb->control;
    }
    else
    {
        /* error TRB type */
        configASSERT(trb_id >= 0);
    }
    erdp_register_update(&xhci_ptr->xer_ring, runtime);
    return event;
}

static void erdp_register_update(xer_event_ring_t *xer_ring,
        volatile xhci_runtime_regs_t *runtime)
{
    uint32_t trb_count;
    uint64_t erdp_addr;

    trb_count = xer_ring->trb_count;

    if (trb_count == 0U)
    {
        erdp_addr = (uint64_t)xer_ring->xer_enqueue_ptr;
        /* EHB flag */
        erdp_addr |= 8UL;
        /* reload the event ring trb count to initial value of EP_TRB_SEG_LENGTH */
        xer_ring->trb_count = XHCI_EVENT_RING_SEG_LENGTH;
    }
    else
    {
        erdp_addr = ((uint64_t) runtime->erdp_hi.value << 32) |
                runtime->erdp_lo.value;
        erdp_addr += 0x10U;
    }
    runtime->erdp_lo.value = (uint32_t) erdp_addr;
    runtime->erdp_hi.value = (uint32_t) (erdp_addr >> 32);
}

xhci_psceg_params_t handle_psceg_event(xpsc_event_t psc_event)
{
    uint32_t temp = 0U;
    xhci_psceg_params_t port_params = { 0 };
    volatile xhci_portsc_20_t *portsc;

    uint8_t rhport = (uint8_t) ((psc_event.buf & 0xff000000UL) >> 24);

    xhci_oper_reg_params_t op_reg = get_xhci_op_registers();
    portsc = (volatile xhci_portsc_20_t *)(uintptr_t)
            (op_reg.xhci_op_base + PORTSC_REG_OFFSET +
             (0x10U * ((uint64_t) rhport - 1UL)));

    if ((portsc->value & USB3_PORTSC_20_CSC_MASK) != 0U)
    {
        /* device connected to RH PORT */
        if ((portsc->value & USB3_PORTSC_20_CCS_MASK) ==
                USB3_PORTSC_20_CCS_MASK)
        {
            /* acknowledge the status bit change */
            temp |= (USB3_PORTSC_20_CSC_MASK);
            port_params.rhport = rhport;
            port_params.dev_attach_flag = 1;
        }
        else
        /* device detach event from RH PORT */
        {
            /* acknowledge the status bit change */
            temp |= (USB3_PORTSC_20_CSC_MASK);
            port_params.rhport = rhport;
            port_params.dev_attach_flag = -1;
        }
    }
    if ((portsc->value & USB3_PORTSC_20_PRC_MASK) != 0U)
    {
        /*Port Reset Event */
        temp |= USB3_PORTSC_20_PRC_MASK;
    }
    if ((portsc->value & USB3_PORTSC_30_WRC_MASK) != 0U)
    {
        /*Warm PR Event */
        temp |= USB3_PORTSC_30_WRC_MASK;
    }

    portsc->value = (portsc->value & ~PORTSC_CLEAR_FLAGS) | temp;

    return port_params;
}

void xhci_warm_reset(uint8_t rhport)
{
    xhci_oper_reg_params_t op_reg = get_xhci_op_registers();
    volatile xhci_portsc_30_t *portsc;

    portsc = (volatile xhci_portsc_30_t *)(uintptr_t)
            (op_reg.xhci_op_base + PORTSC_REG_OFFSET +
             (0x10U * ((uint64_t) rhport - 1UL)));

    portsc->value |= USB3_PORTSC_30_WPR_MASK;
}
