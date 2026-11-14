/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Header file for Interrupts sub-module of SoC FPGA USB3.1 XHCI low level driver
 */

#ifndef __XHCI_INTERRUPTS_H__
#define __XHCI_INTERRUPTS_H__

#include <stdbool.h>

/*
 * @brief  enable xhci interrupts
 */
void enable_xhci_interrupts(void);

/*
 * @brief  disable the xhci interrupts
 */
void disable_xhci_interrupts(void);

/*
 * @brief Acknowledge a pending xHCI interrupt; resets the controller on HSE/HCE
 * @return true if the event ring should be processed
 */
bool xhci_irq_ack(void);

#endif  /* __XHCI_INTERRUPTS_H__ */
