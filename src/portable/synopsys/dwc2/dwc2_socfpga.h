/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Ha Thach (tinyusb.org)
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

// DWC2 vendor header for Altera SoC FPGA (Agilex 5): USB2.0 OTG controller (USB0).
// All SoC specifics of the DWC2 port live here; hcd_dwc2.c / dwc2_common.c stay vendor-neutral.

#ifndef DWC2_SOCFPGA_H_
#define DWC2_SOCFPGA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "socfpga_usb_otg_reg.h"
#include "socfpga_interrupt.h"
#include "socfpga_interrupt_priority.h"
#include "socfpga_rst_mngr.h"
#include "socfpga_cache.h"
#include "osal_log.h"

// Toggle a GPIO to reset the external USB2 PHY before controller init (board dependent)
#ifndef USB_GPIO_TOGGLE
  #define USB_GPIO_TOGGLE 0
#endif

#if USB_GPIO_TOGGLE
  #include "socfpga_gpio.h"
  #include "socfpga_defines.h"
#endif

#define DWC2_EP_MAX   15

// On Agilex5 socfpga, we associate:
// - Port0 to USB_OTG (USB0)
static const dwc2_controller_t _dwc2_controller[] = {
  { .reg_base = USBOTG_BASE_ADDR, .irqnum = USB0IRQ, .ep_count = DWC2_EP_MAX, .ep_fifo_size = 8192 },
};

//--------------------------------------------------------------------+
// Interrupt
//--------------------------------------------------------------------+
extern void tusb_int_handler(uint8_t rhport, bool in_isr);

// GIC callback: forward to the stack, which routes to host/device by the role of this rhport
static void dwc2_socfpga_isr(void* data) {
  tusb_int_handler((uint8_t) (uintptr_t) data, true);
}

TU_ATTR_ALWAYS_INLINE static inline void dwc2_int_set(uint8_t rhport, tusb_role_t role, bool enabled) {
  (void) role;
  const socfpga_hpu_interrupt_t irqn = (socfpga_hpu_interrupt_t) _dwc2_controller[rhport].irqnum;

  if (enabled) {
    if (interrupt_register_isr(irqn, dwc2_socfpga_isr, (void*) (uintptr_t) rhport) != 0) {
      ERROR("Failed to register usb2 interrupt");
      return;
    }
    if (interrupt_enable(irqn, GIC_INTERRUPT_PRIORITY_USB2) != 0) {
      ERROR("Failed to enable usb2 interrupt");
      return;
    }
  } else {
    (void) interrupt_disable(irqn);
  }
}

#define dwc2_dcd_int_enable(_rhport)  dwc2_int_set(_rhport, TUSB_ROLE_DEVICE, true)
#define dwc2_dcd_int_disable(_rhport) dwc2_int_set(_rhport, TUSB_ROLE_DEVICE, false)

TU_ATTR_ALWAYS_INLINE static inline void dwc2_remote_wakeup_delay(void) {
  // try to delay for 1 ms
  osal_task_delay(1);
}

//--------------------------------------------------------------------+
// Controller bring-up: optional GPIO PHY reset + SoC reset manager
//--------------------------------------------------------------------+
#if USB_GPIO_TOGGLE
#define DWC2_SOCFPGA_GPIO_USB_RESET GPIO1_PIN4

static bool dwc2_socfpga_gpio_reset(void) {
  // route the pin to GPIO in pinmux if needed
  uint32_t reg_val = RD_REG32(PINMUX_REG(DWC2_SOCFPGA_GPIO_USB_RESET));
  if ((reg_val & PINMUX_MASK) != PINMUX_GPIO) {
    WR_REG32(PINMUX_REG(DWC2_SOCFPGA_GPIO_USB_RESET), (reg_val & ~PINMUX_MASK) | PINMUX_GPIO);
  }

  gpio_handle_t gpio = gpio_open(DWC2_SOCFPGA_GPIO_USB_RESET);
  int dir = GPIO_DIR_OUT;
  if (gpio_ioctl(gpio, SET_GPIO_DIR, &dir) != 0) {
    ERROR("usb2 gpio reset failed");
    gpio_close(gpio);
    return false;
  }

  gpio_write_sync(gpio, 1);
  osal_task_delay(10);
  return true;
}
#endif

#define DWC2_MCU_INIT_HOOK
TU_ATTR_ALWAYS_INLINE static inline bool dwc2_mcu_init(uint8_t rhport) {
  (void) rhport;
#if USB_GPIO_TOGGLE
  TU_ASSERT(dwc2_socfpga_gpio_reset());
#endif
  TU_ASSERT(rstmgr_assert_reset(RST_USB0) == 0);
  TU_ASSERT(rstmgr_deassert_reset(RST_USB0) == 0);
  TU_ASSERT(rstmgr_deassert_reset(RST_USB0ECC) == 0);
  return true;
}

//--------------------------------------------------------------------+
// PHY
//--------------------------------------------------------------------+

// MCU specific PHY init, called BEFORE core reset.
// Kept identical to the previous socfpga port (inherited from the STM32 header): it toggles bit 16 of
// GGPIO (offset 0x38, "stm32_gccfg" in dwc2_type.h). TODO: confirm on Agilex 5 whether this is required.
TU_ATTR_ALWAYS_INLINE static inline void dwc2_phy_init(dwc2_regs_t* dwc2, uint8_t hs_phy_type) {
  if (hs_phy_type == GHWCFG2_HSPHY_NOT_SUPPORTED) {
    dwc2->stm32_gccfg |= STM32_GCCFG_PWRDWN;
  } else {
    dwc2->stm32_gccfg &= ~STM32_GCCFG_PWRDWN;
  }
}

// MCU specific PHY update, it is called AFTER init() and core reset
TU_ATTR_ALWAYS_INLINE static inline void dwc2_phy_update(dwc2_regs_t* dwc2, uint8_t hs_phy_type) {
  (void) dwc2;
  (void) hs_phy_type;
}

//--------------------------------------------------------------------+
// DCache (only used when CFG_TUH_MEM_DCACHE_ENABLE / CFG_TUD_MEM_DCACHE_ENABLE)
//--------------------------------------------------------------------+
#if CFG_TUD_MEM_DCACHE_ENABLE || CFG_TUH_MEM_DCACHE_ENABLE

TU_ATTR_ALWAYS_INLINE static inline uint32_t round_up_to_cache_line_size(uint32_t size) {
  if (size & (CFG_TUSB_MEM_DCACHE_LINE_SIZE_DEFAULT - 1)) {
    size = (size & ~(CFG_TUSB_MEM_DCACHE_LINE_SIZE_DEFAULT - 1)) + CFG_TUSB_MEM_DCACHE_LINE_SIZE_DEFAULT;
  }
  return size;
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc2_dcache_clean(void const* addr, uint32_t data_size) {
  cache_force_write_back((void*) (uintptr_t) addr, (size_t) round_up_to_cache_line_size(data_size));
  return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc2_dcache_invalidate(void const* addr, uint32_t data_size) {
  cache_force_invalidate((void*) (uintptr_t) addr, (size_t) round_up_to_cache_line_size(data_size));
  return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool dwc2_dcache_clean_invalidate(void const* addr, uint32_t data_size) {
  // write back first, then invalidate, so dirty lines are not discarded
  data_size = round_up_to_cache_line_size(data_size);
  cache_force_write_back((void*) (uintptr_t) addr, (size_t) data_size);
  cache_force_invalidate((void*) (uintptr_t) addr, (size_t) data_size);
  return true;
}
#endif

#ifdef __cplusplus
}
#endif

#endif
