/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 Altera Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

// DWC3 vendor header for Altera SoC FPGA (Agilex 5): USB3.1 controller (USB1) in xHCI host mode.
// All SoC specifics of the DWC3 port live here; hcd_dwc3.c / dwc3_common.c / xhci stay vendor-neutral.

#ifndef DWC3_SOCFPGA_H_
#define DWC3_SOCFPGA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "socfpga_defines.h"
#include "socfpga_interrupt.h"
#include "socfpga_interrupt_priority.h"
#include "socfpga_rst_mngr.h"
#include "socfpga_cache.h"
#include "osal_log.h"

// USB3.1 controller base address
#define DWC3_REG_BASE   (0x11000000U)

// TinyUSB rhport of each xHCI root-hub port (rhport == xHCI port number):
// - port 1: USB2.0 (HS/FS/LS) port, owns the interrupt
// - port 2: USB3.x SuperSpeed port, owns controller init
#ifndef DWC3_RHPORT_HS
  #define DWC3_RHPORT_HS  1
#endif
#ifndef DWC3_RHPORT_SS
  #define DWC3_RHPORT_SS  2
#endif

#define DWC3_IRQ        USB1IRQ

//--------------------------------------------------------------------+
// Interrupt
//--------------------------------------------------------------------+
extern void tusb_int_handler(uint8_t rhport, bool in_isr);

// GIC callback: all xHCI events are reported through the HS rhport
static void dwc3_socfpga_isr(void* data) {
  (void) data;
  tusb_int_handler(DWC3_RHPORT_HS, true);
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc3_int_set(uint8_t rhport, bool enabled) {
  (void) rhport;
  if (enabled) {
    if (interrupt_register_isr(DWC3_IRQ, dwc3_socfpga_isr, NULL) != 0) {
      ERROR("Failed to register usb3 interrupt");
      return false;
    }
    if (interrupt_enable(DWC3_IRQ, GIC_INTERRUPT_PRIORITY_USB3) != 0) {
      ERROR("Failed to enable usb3 interrupt");
      return false;
    }
  } else {
    (void) interrupt_disable(DWC3_IRQ);
  }
  return true;
}

//--------------------------------------------------------------------+
// Controller bring-up
//--------------------------------------------------------------------+
TU_ATTR_ALWAYS_INLINE static inline bool dwc3_mcu_init(uint8_t rhport) {
  (void) rhport;
  if (rstmgr_deassert_reset(RST_USB1) != 0) {
    ERROR("Unable to deassert the usb3 reset");
    return false;
  }
  return true;
}

//--------------------------------------------------------------------+
// DCache
//--------------------------------------------------------------------+
TU_ATTR_ALWAYS_INLINE static inline void dwc3_dcache_clean(void* addr, size_t size) {
  cache_force_write_back(addr, size);
}

TU_ATTR_ALWAYS_INLINE static inline void dwc3_dcache_invalidate(void* addr, size_t size) {
  cache_force_invalidate(addr, size);
}

//--------------------------------------------------------------------+
// Memory for xHCI rings and contexts
// TODO: the xHCI library still allocates dynamically; move to static pools (refactor/usb3-static-buffer)
//--------------------------------------------------------------------+
#define DWC3_MEM_ALLOC(_size)                  pvPortMalloc(_size)
#define DWC3_MEM_ALLOC_ALIGNED(_align, _size)  pvPortAlignedAlloc(_align, _size)
#define DWC3_MEM_ALLOC_COHERENT(_size)         pvPortMallocCoherent(_size)
#define DWC3_MEM_FREE(_ptr)                    vPortFree(_ptr)

#ifdef __cplusplus
}
#endif

#endif
