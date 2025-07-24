/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Header file for xHCI implementation
 */

#ifndef __HCD_SOCFPGA_H__
#define __HCD_SOCFPGA_H__

#include <stdio.h>
#include "xhci.h"
#include "xhci_events.h"

#define XHCI_SPEED_LS    (1)
#define XHCI_SPEED_FS    (2)
#define XHCI_SPEED_HS    (3)
#define XHCI_SPEED_SS    (4U)

#define XHCI_QUEUE_SZ    (10U)

typedef struct
{
    /* reference to xHCI structure */
    struct xhci_data xhci_priv __attribute__((aligned(64)));
}Usb3_Handle_t;

/*
 * @brief  allocate all the usb3 port memory
 * @return
 *  xHanlde  reference to Usb3_Handle_t structure
 */
Usb3_Handle_t*alloc_usb_port(void);

/*
 * @brief  deallocate all the usb3 port memory
 * @param[in] handle usb3 port reference handle
 */
void dealloc_usb_port(Usb3_Handle_t*handle);

/*
 * @brief api to check whether the reset process has completed or not
 * @param[in] rhport portid of the correspondinf port
 * @return
 *  - true, if operation is successul,
 *  - false, if the operation fails
 */
bool usb_port_reset_end(uint8_t rhport);

/*
 * @brief  common usb api to reset the port
 * @param[in] rhport RH port number
 */
void reset_usb_port(uint8_t rhport);

/*
 * @brief  initialize the HCD queue
 * @return
 *  0, if initalization is successful,
 *  errno, incase of any failure
 */
int init_hcd_params(void);

/*
 * @brief wait for the command completio event
 * @param[in] xhci_ptr reference to xhci context data structure
 * @param[in[ type to specify the type of command completed by xHCI
 * @return
 *  - NO_ERROR, if command is executed succssfully
 *  - -1, if command completion event reports failure
 */
int wait_for_command_completion_event(struct xhci_data *xhci_ptr, int type);

/*
 * @brief  notify about the completion of command ring operation
 * @param[in] command completion event params
 */
void xhci_command_event_complete(xcc_event_t event);

#endif  /* __HCD_SOCFPGA_H__ */
