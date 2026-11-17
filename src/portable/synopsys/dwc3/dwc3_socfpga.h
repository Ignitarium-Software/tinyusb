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

#ifdef __cplusplus
extern "C" {
#endif

#if CFG_TUSB_MCU == OPT_MCU_SOCFPGA
  #define SOCFPGA_USB3_REG_BASE     (0x1100C100U)
  #define OTG_HS_IRQn               126 // IRQ num for USB1 = 126
  #include "socfpga_interrupt.h"
  #include "socfpga_interrupt_priority.h"
  #include "socfpga_rst_mngr.h"
#else
  #error "Unsupported MCUs"
#endif

// On STM32 for consistency we associate
// - Port0 to OTG_FS, and Port1 to OTG_HS
static const dwc3_controller_t _dwc3_controller[] = {
    { .reg_base = SOCFPGA_USB3_REG_BASE, .irqnum = OTG_HS_IRQn, },
};

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
