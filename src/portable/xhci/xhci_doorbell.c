/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Low level driver implementation for SoC FPGA USB3.1 XHCI controller.
 * Doorbell submodule.
 */

#include "xhci_doorbell.h"

void ring_xhci_host_db(void)
{
    xhci_oper_reg_params_t op_regs;
    volatile xhci_db_t *doorbells;

    op_regs = get_xhci_op_registers();
    doorbells = (volatile xhci_db_t *)(uintptr_t) op_regs.xhci_db_base;
    doorbells[0].value = XHCI_COMMAND_DOORBELL;
}
void ring_xhci_ep0_db(xhci_oper_reg_params_t *op_regs)
{
    volatile xhci_db_t *doorbells;
    uint32_t slot_id = 1U;

    doorbells = (volatile xhci_db_t *)(uintptr_t) op_regs->xhci_db_base;
    doorbells[slot_id].value = XHCI_DB_EP0_TARGET;
}

void ring_xhci_ep_doorbell(xhci_oper_reg_params_t *op_regs, uint8_t db_target)
{
    volatile xhci_db_t *doorbells;
    uint32_t slot_id = 1U;

    doorbells = (volatile xhci_db_t *)(uintptr_t) op_regs->xhci_db_base;
    doorbells[slot_id].value = db_target;
}
