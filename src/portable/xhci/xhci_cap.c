/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Low level driver implementation for SoC FPGA USB3.1 XHCI controller.
 * Capabilities sub-module
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "xhci.h"
#include "host/hcd.h"

/*
 * @brief read the host controller capability registers
 */
int get_xhc_cap_params(struct xhci_data *xhci)
{
    volatile xhci_regs_t *regs =
            (volatile xhci_regs_t *)(uintptr_t) USBBASE;

    xhci->xhc_cap_ptr = (xhci_cap_reg_t *)USBBASE;

    TU_LOG2("CAPLENGTH : %x",
            (regs->caplength.value & USB3_CAPLENGTH_CAPLENGTH_MASK));
    TU_LOG2("HCSPARAMS1 : %x",
            regs->hcsparams1.value);
    TU_LOG2("HCSPARAMS2 : %x",
            regs->hcsparams2.value);
    TU_LOG2("HCSPARAMS3 : %x",
            regs->hcsparams3.value);
    TU_LOG2("HCCPARAMS1 : %x",
            regs->hccparams1.value);
    TU_LOG2("DBOFF : %x",
            (regs->dboff.value &
             USB3_DBOFF_DOORBELL_ARRAY_OFFSET_MASK));
    TU_LOG2("RTOFF : %x",
            (regs->rtsoff.value &
             USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET_MASK));
    TU_LOG2("HCCPARAMS2 : %x",
            regs->hccparams2.value);

    xhci->op_regs.xhci_op_base = (uint64_t)USBBASE +
            (uint64_t)(regs->caplength.value &
                       USB3_CAPLENGTH_CAPLENGTH_MASK);
    xhci->op_regs.xhci_runtime_base = (uint64_t)USBBASE +
            (uint64_t)(regs->rtsoff.value &
                       USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET_MASK);
    xhci->op_regs.xhci_db_base = (uint64_t)USBBASE +
            (uint64_t)(regs->dboff.value &
                       USB3_DBOFF_DOORBELL_ARRAY_OFFSET_MASK);

    TU_LOG2("Operational base : %lx ",
            xhci->op_regs.xhci_op_base);
    TU_LOG2("Runtime  base : %lx ",
            xhci->op_regs.xhci_runtime_base);
    TU_LOG2("Doorbell base : %lx ",
            xhci->op_regs.xhci_db_base);

    return 0;
}

xhci_oper_reg_params_t get_xhci_op_registers(void)
{
    xhci_oper_reg_params_t op_reg = {0};
    volatile xhci_regs_t *regs =
            (volatile xhci_regs_t *)(uintptr_t) USBBASE;
    /* CAPLENGTH[7:0] */
    op_reg.xhci_op_base = (uint64_t)USBBASE +
            (uint64_t)(regs->caplength.value &
                       USB3_CAPLENGTH_CAPLENGTH_MASK);
    /* DBOFF[31:2] */
    op_reg.xhci_db_base = (uint64_t)USBBASE +
            (uint64_t)(regs->dboff.value &
                       USB3_DBOFF_DOORBELL_ARRAY_OFFSET_MASK);
    /* RSTOFF[31:5] */
    op_reg.xhci_runtime_base = (uint64_t)USBBASE +
            (uint64_t)(regs->rtsoff.value &
                       USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET_MASK);
    return op_reg;
}
