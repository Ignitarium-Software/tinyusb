/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Ha Thach (tinyusb.org)
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

#include "tusb_option.h"

#if CFG_TUH_ENABLED && defined(TUP_USBIP_DWC2) && !CFG_TUH_MAX3421

#include "host/hcd.h"
#include "host/usbh.h"
#include "dwc3_common.h"
#include "xhci_api.h"

//--------------------------------------------------------------------+
// Controller API
//--------------------------------------------------------------------+

// Initialize controller to host mode
bool hcd_init(uint8_t rhport, const tusb_rhport_init_t* rh_init) {

  (void) rh_init;

  if (rhport == 1)
    return true;

  dwc3_gbl_regs_t* dwc3 = (dwc3_gbl_regs_t*) (uintptr_t) _dwc3_controller[0].reg_base;

  dwc3_mcu_init(rhport);

  const dwc3_ghwparams0_t ghwparams0 = {.value = dwc3->ghwparams0.value};
  const dwc3_ghwparams1_t ghwparams1 = {.value = dwc3->ghwparams1.value};
  const dwc3_ghwparams3_t ghwparams3 = {.value = dwc3->ghwparams3.value};

  switch (ghwparams3.ghwparams3_1_0) {
    case DWC3_SS_PHY_3_0:
      INFO("Device supportes USB 3.0 Only");
      break;

    case DWC3_SS_PHY_3_1:
      INFO("Device supportes USB 3.1 Gen1");
      break;

    default:
      INFO("Device does not support USB3.1");
      break;
  }

  printf("HWPARAMS : %x, %x, %x\r\n", ghwparams0.value,  ghwparams1.value, ghwparams3.value);

  switch (ghwparams3.ghwparams3_3_2) {
    case DWC3_HS_PHY_UTMI:
    case DWC3_HS_PHY_ULPI:
      break;

    case DWC3_HS_PHY_UTMI_ULPI: {
      dwc3_gusb2_phycfg_t gusb2_phycfg = {.value = dwc3->gusb2_phycfg.value};
      gusb2_phycfg.ulpi_utmi_sel = 1;
      dwc3->gusb2_phycfg.value = gusb2_phycfg.value;
      break;
    }

    default:
      break;
  }

  dwc3_gctl_t gctl = {.value = dwc3->gctl.value};
  gctl.scaledown = 0;
  switch (ghwparams1.ghwparams1_25_24) {
    case 1:
      gctl.dsblclkgtng = 0;
      break;

    case 2:
      gctl.gbl_hibernation_en = 1;
      break;

    default:
      break;
  }
  dwc3->gctl.value = gctl.value;

  switch (ghwparams0.ghwparams0_2_0) {
    case DWC3_GHWPARAMS0_MODE_DRD: {
      dwc3_gusb3_pipectl_t gusb3_pipectl = {.value = dwc3->gusb3_pipectl.value};
      gusb3_pipectl.suspendenable = 0;
      dwc3->gusb3_pipectl.value = gusb3_pipectl.value;

      dwc3_gusb2_phycfg_t gusb2_phycfg = {.value = dwc3->gusb2_phycfg.value};
      gusb2_phycfg.suspendusb20 = 0;
      dwc3->gusb2_phycfg.value = gusb2_phycfg.value;

      gctl.value = dwc3->gctl.value;
      gctl.prtcapdir = USB_MODE_HOST;
      dwc3->gctl.value = gctl.value;

      gctl.value = dwc3->gctl.value;
      gctl.coresoftreset = 1;
      dwc3->gctl.value = gctl.value;

      osal_task_delay(100);

      gctl.value = dwc3->gctl.value;
      gctl.coresoftreset = 0;
      dwc3->gctl.value = gctl.value;

      gusb2_phycfg.value = dwc3->gusb2_phycfg.value;
      gusb2_phycfg.suspendusb20 = 1;
      dwc3->gusb2_phycfg.value = gusb2_phycfg.value;

      gusb3_pipectl.value = dwc3->gusb3_pipectl.value;
      gusb3_pipectl.suspendenable = 1;
      dwc3->gusb3_pipectl.value = gusb3_pipectl.value;
      break;
    }

    case DWC3_GHWPARAMS0_MODE_HOST:
      break;

    default:
      ERROR("Unable to setup DWC3 in host mode");
      return false;
  }

  if (xhci_init() == false)
  {
    ERROR("xHCI init failed !!!");
    return false;
  }

  return true;
}

#if 0
// Enable USB interrupt
void hcd_int_enable (uint8_t rhport) {
  dwc2_int_set(rhport, TUSB_ROLE_HOST, true);
}

// Disable USB interrupt
void hcd_int_disable(uint8_t rhport) {
  dwc2_int_set(rhport, TUSB_ROLE_HOST, false);
}

#endif
#endif
