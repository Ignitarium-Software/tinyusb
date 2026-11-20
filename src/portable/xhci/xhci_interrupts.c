/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Low level driver implementation for SoC FPGA USB3.1 XHCI controller.
 * Interrupt sub-module.
 */

#include "xhci.h"
#include "xhci_interrupts.h"
#include "socfpga_interrupt.h"
#include "socfpga_interrupt_priority.h"
#include "host/hcd.h"

void socfpga_usb3_handler(void *handler);

void enable_xhci_interrupts(void)
{
    struct xhci_oper_reg_params op_regs;
    volatile xhci_runtime_regs_t *runtime;
    volatile xhci_regs_t *xhci;

    op_regs = get_xhci_op_registers();
    runtime = (volatile xhci_runtime_regs_t *)(uintptr_t) op_regs.xhci_runtime_base;
    xhci = (volatile xhci_regs_t *)(uintptr_t) USBBASE;

    runtime->iman.ie = 1U;
    xhci->usbcmd.inte = 1U;
}

void disable_xhci_interrupts(void)
{

    struct xhci_oper_reg_params op_regs;
    volatile xhci_runtime_regs_t *runtime;
    volatile xhci_regs_t *xhci;

    op_regs = get_xhci_op_registers();
    runtime = (volatile xhci_runtime_regs_t *)(uintptr_t) op_regs.xhci_runtime_base;
    xhci = (volatile xhci_regs_t *)(uintptr_t) USBBASE;

    runtime->iman.ie = 0U;
    runtime->iman.ip = 0U;
    xhci->usbcmd.inte = 0U;
}

bool register_usb3ISR(xhci_int_ptr_t int_handler)
{
    int err;

    err = interrupt_register_isr(USB1IRQ, socfpga_usb3_handler,
            int_handler);
    if (err != 0)
    {
        return false;
    }

    err = interrupt_enable(USB1IRQ, GIC_INTERRUPT_PRIORITY_USB3);
    if (err != 0)
    {
        TU_LOG1("Failed to enable interrupt");
        return false;
    }

    TU_LOG3("Interrupt handler registered successfully");
    return true;
}

void socfpga_usb3_handler(void *handler)
{
    xhci_int_ptr_t usb3_int_handler;
    struct xhci_oper_reg_params op_regs;
    volatile xhci_runtime_regs_t *runtime;
    volatile xhci_regs_t *xhci;

    op_regs = get_xhci_op_registers();
    runtime = (volatile xhci_runtime_regs_t *)(uintptr_t) op_regs.xhci_runtime_base;
    xhci = (volatile xhci_regs_t *)(uintptr_t) USBBASE;

    usb3_int_handler = (xhci_int_ptr_t) handler;

    if ((xhci->usbsts.hse != 0U) || (xhci->usbsts.hce != 0U))
    {
        (void) xhci_reset();
        start_xhci_controller();
        return;
    }

    xhci->usbsts.eint = 1U;
    runtime->iman.ip = 1U;

    /* rh_port = 1 -> RH port number as per tinyusb stack */
    /* in_isr = true, ISR flag for tinyusb stack */
    usb3_int_handler->int_handler(1, true);
}
