/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021, Ha Thach (tinyusb.org)
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

#ifndef DWC3_SOCFPGA_H_
#define DWC3_SOCFPGA_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if CFG_TUSB_MCU == OPT_MCU_SOCFPGA
  #define SOCFPGA_USB3_REG_BASE     (0x1100C100U)
  #define OTG_HS_IRQn               126 // IRQ num for USB1 = 126
  #include "socfpga_interrupt.h"
  #include "socfpga_interrupt_priority.h"
  #include "socfpga_rst_mngr.h"
  #include "socfpga_cache.h"
#else
  #error "Unsupported MCUs"
#endif

// On STM32 for consistency we associate
// - Port0 to OTG_FS, and Port1 to OTG_HS
static const dwc3_controller_t _dwc3_controller[] = {
    { .reg_base = SOCFPGA_USB3_REG_BASE, .irqnum = OTG_HS_IRQn, },
};

//------------- DCache -------------//
#if CFG_TUH_MEM_DCACHE_ENABLE

TU_ATTR_ALWAYS_INLINE static inline bool dwc3_dcache_aligned_range(void const* addr, uint32_t data_size,
                                                                  uint32_t** aligned_addr, int32_t* aligned_size) {
  const uintptr_t line_size = CFG_TUSB_MEM_DCACHE_LINE_SIZE_DEFAULT;
  const uintptr_t line_mask = line_size - 1U;
  const uintptr_t start = (uintptr_t) addr;

  if ((line_size == 0U) || ((line_size & line_mask) != 0U) ||
      (addr == NULL) || (data_size == 0U) || (start > UINTPTR_MAX - data_size)) {
    return false;
  }

  const uintptr_t aligned_start = start & ~line_mask;
  const uintptr_t end = start + data_size;
  if (end > UINTPTR_MAX - line_mask) {
    return false;
  }

  const uintptr_t aligned_end = (end + line_mask) & ~line_mask;
  const uintptr_t range_size = aligned_end - aligned_start;
  if (range_size > INT32_MAX) {
    return false;
  }

  *aligned_addr = (uint32_t*) aligned_start;
  *aligned_size = (int32_t) range_size;
  return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc3_dcache_clean(void const* addr, uint32_t data_size) {
  if (data_size == 0U) {
    return true;
  }

  uint32_t* aligned_addr;
  int32_t aligned_size;
  if (!dwc3_dcache_aligned_range(addr, data_size, &aligned_addr, &aligned_size)) {
    return false;
  }

  cache_force_write_back(aligned_addr, aligned_size);
  return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc3_dcache_invalidate(void const* addr, uint32_t data_size) {
  if (data_size == 0U) {
    return true;
  }

  uint32_t* aligned_addr;
  int32_t aligned_size;
  if (!dwc3_dcache_aligned_range(addr, data_size, &aligned_addr, &aligned_size)) {
    return false;
  }

  cache_force_invalidate(aligned_addr, aligned_size);
  return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc3_dcache_clean_invalidate(void const* addr, uint32_t data_size) {
  if (data_size == 0U) {
    return true;
  }

  uint32_t* aligned_addr;
  int32_t aligned_size;
  if (!dwc3_dcache_aligned_range(addr, data_size, &aligned_addr, &aligned_size)) {
    return false;
  }

  cache_force_write_back(aligned_addr, aligned_size);
  cache_force_invalidate(aligned_addr, aligned_size);
  return true;
}
#endif

//--------------------------------------------------------------------+
// Controller bring-up
//--------------------------------------------------------------------+
TU_ATTR_ALWAYS_INLINE static inline bool dwc3_mcu_init(uint8_t rhport) {
  (void) rhport;
  if (rstmgr_deassert_reset(_dwc3_controller[0].irqnum) != 0) {
    return false;
  }
  return true;
} 

#ifdef __cplusplus
}
#endif

#endif
