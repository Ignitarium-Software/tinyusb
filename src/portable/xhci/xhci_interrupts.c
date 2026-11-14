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
#include "xhci_port.h"

void enable_xhci_interrupts(void)
{
    volatile uint32_t reg_val;
    struct xhci_oper_reg_params op_regs;

    op_regs = get_xhci_op_registers();

    reg_val = RD_REG32((op_regs.xhci_runtime_base + USB3_IMAN));
    reg_val |= USB3_IMAN_IE_MASK;
    WR_REG32((op_regs.xhci_runtime_base + USB3_IMAN), reg_val);

    reg_val = RD_REG32((XHCI_BASE_ADDR + USB3_USBCMD));
    reg_val |= USB3_USBCMD_INTE_MASK;
    WR_REG32((XHCI_BASE_ADDR + USB3_USBCMD), reg_val);
}

void disable_xhci_interrupts(void)
{

    volatile uint32_t reg_val;
    struct xhci_oper_reg_params op_regs;

    op_regs = get_xhci_op_registers();

    reg_val = RD_REG32((op_regs.xhci_runtime_base + USB3_IMAN));
    reg_val &= ~(USB3_IMAN_IE_MASK);
    WR_REG32((op_regs.xhci_runtime_base + USB3_IMAN), reg_val);

    reg_val = RD_REG32((op_regs.xhci_runtime_base + USB3_IMAN));
    reg_val &= ~(USB3_IMAN_IP_MASK);
    WR_REG32((op_regs.xhci_runtime_base + USB3_IMAN), reg_val);

    reg_val = RD_REG32((XHCI_BASE_ADDR + USB3_USBCMD));
    reg_val &= ~(USB3_USBCMD_INTE_MASK);
    WR_REG32((XHCI_BASE_ADDR + USB3_USBCMD), reg_val);
}

/*
 * @brief Acknowledge a pending xHCI interrupt (USBSTS.EINT and IMAN.IP of interrupter 0).
 * On Host System Error / Host Controller Error the controller is reset and restarted.
 * @return true if event ring processing should follow, false otherwise
 */
bool xhci_irq_ack(void)
{
    uint32_t reg_val;
    struct xhci_oper_reg_params op_regs;

    op_regs = get_xhci_op_registers();

    reg_val = RD_REG32((XHCI_BASE_ADDR + USB3_USBSTS));

    if (((reg_val & USB3_USBSTS_HSE_MASK) != 0U) || ((reg_val &
            USB3_USBSTS_HCE_MASK) != 0U))
    {
        (void) xhci_reset();
        start_xhci_controller();
        return false;
    }

    reg_val |= (USB3_USBSTS_EINT_MASK);
    WR_REG32((XHCI_BASE_ADDR + USB3_USBSTS), reg_val);

    reg_val = RD_REG32((op_regs.xhci_runtime_base + USB3_IMAN));
    reg_val |= USB3_IMAN_IP_MASK;
    WR_REG32((op_regs.xhci_runtime_base + USB3_IMAN), reg_val);

    return true;
}
