/*
 * SPDX-FileCopyrightText: Copyright (C) 2025-2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Synopsys DWC3 core: common definitions and core (global register) helpers.
 */

#ifndef TUSB_DWC3_COMMON_H_
#define TUSB_DWC3_COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "common/tusb_common.h"
#include "dwc3_type.h"

// Following symbols must be defined by the vendor header:
// - DWC3_REG_BASE                          : base address of the DWC3 core (xHCI registers at offset 0)
// - DWC3_RHPORT_HS / DWC3_RHPORT_SS        : TinyUSB rhport of the xHCI USB2 / USB3 root-hub port.
//                                            The driver uses rhport == xHCI root-hub port number.
// - dwc3_mcu_init()                        : release the core from SoC reset, clocks, PHY
// - dwc3_int_set(rhport, enabled)          : register/enable or disable the controller IRQ
// - dwc3_dcache_clean/dwc3_dcache_invalidate(void*, size_t)
// - DWC3_MEM_ALLOC/_ALIGNED/_COHERENT/DWC3_MEM_FREE : memory for xHCI rings and contexts
// - RD_REG32/WR_REG32/WR_REG64 (optional, generic volatile access otherwise) and INFO/DEBUG/ERROR logs

#if TU_CHECK_MCU(OPT_MCU_SOCFPGA)
  #include "dwc3_socfpga.h"
#else
  #error "Unsupported MCUs"
#endif

#ifndef RD_REG32
  #define RD_REG32(_addr)        (*(volatile uint32_t const*) (uintptr_t) (_addr))
#endif
#ifndef WR_REG32
  #define WR_REG32(_addr, _val)  (*(volatile uint32_t*) (uintptr_t) (_addr) = (uint32_t) (_val))
#endif

//--------------------------------------------------------------------+
// Glue consumed by the generic xHCI library (src/portable/xhci/xhci_port.h)
//--------------------------------------------------------------------+
#define XHCI_BASE_ADDR                         DWC3_REG_BASE
#define xhci_dcache_clean(_addr, _size)        dwc3_dcache_clean((void*) (_addr), (size_t) (_size))
#define xhci_dcache_invalidate(_addr, _size)   dwc3_dcache_invalidate((void*) (_addr), (size_t) (_size))
#define XHCI_MEM_ALLOC(_size)                  DWC3_MEM_ALLOC(_size)
#define XHCI_MEM_ALLOC_ALIGNED(_align, _size)  DWC3_MEM_ALLOC_ALIGNED(_align, _size)
#define XHCI_MEM_ALLOC_COHERENT(_size)         DWC3_MEM_ALLOC_COHERENT(_size)
#define XHCI_MEM_FREE(_ptr)                    DWC3_MEM_FREE(_ptr)

#define USB_MODE_HOST                  ((uint32_t) 1) /* !< USB host mode */

#define DWC3_HS_PHY_DIS                (0U) /* !< HS phy is disabled */
#define DWC3_HS_PHY_UTMI               (1U) /* !< HS phy interface is UTMI */
#define DWC3_HS_PHY_ULPI               (2U) /* !< HS phy interface is ULPI */
#define DWC3_HS_PHY_UTMI_ULPI          (3U) /* !< DWC3 supports both UTMI/ULPI HS phy interface */

#define DWC3_SS_PHY_DIS                (0U) /* !< DWC3 SS phy interface is disabled */
#define DWC3_SS_PHY_3_0                (1U) /* !< DWC3 supports only USB3.0 mode */
#define DWC3_SS_PHY_3_1                (2U) /* !< DWC3 supports USB3.1 mode */

#define DWC3_GHWPARAMS0_MODE_GADGET    (0U) /* !< DWC3 Core is in gadget mode */
#define DWC3_GHWPARAMS0_MODE_HOST      (1U) /* !< DWC3 Core is in host mode*/
#define DWC3_GHWPARAMS0_MODE_DRD       (2U) /* !< DWC3 Core is in DRD mode*/


/**
 * @brief Initialize the DWC3 core in host (xHCI) mode
 * @return 0 on success, errno otherwise
 */
int dwc3_init(void);

#endif /* TUSB_DWC3_COMMON_H_ */
