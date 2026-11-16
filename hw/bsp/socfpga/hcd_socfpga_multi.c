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

// Agilex 5 host controller map for CFG_TUH_HCD_MULTI (SOCFPGA_HCD=both):
//   rhport 0 : USB0, DWC2 USB2.0 OTG
//   rhport 1 : USB1, DWC3 xHCI root-hub port 1 (USB2.0), owns the interrupt
//   rhport 2 : USB1, DWC3 xHCI root-hub port 2 (USB3.x), owns controller init

#include "tusb_option.h"

#if CFG_TUH_ENABLED && CFG_TUH_HCD_MULTI

#include "host/hcd.h"
#include "common/tusb_private.h"

TU_VERIFY_STATIC(CFG_TUH_HCD_MULTI_COUNT == 3, "Agilex 5 map has 3 rhport entries");
TU_VERIFY_STATIC(CFG_TUH_HCD_MULTI_COUNT <= TUP_USBIP_CONTROLLER_NUM, "rhport entries exceed controller number");

TUH_HCD_DRIVER_DEFINE(dwc2);
TUH_HCD_DRIVER_DEFINE(dwc3);

hcd_driver_t const* const tuh_hcd_drivers[CFG_TUH_HCD_MULTI_COUNT] = {
  [0] = &hcd_dwc2_driver,
  [1] = &hcd_dwc3_driver,
  [2] = &hcd_dwc3_driver,
};

#endif
