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

/* Multiple host controller drivers (CFG_TUH_HCD_MULTI)
 * ===================================================
 *
 * Every TinyUSB HCD implements the same fixed API from host/hcd.h (hcd_init, hcd_edpt_xfer, ...).
 * To link several unmodified HCDs into one image, each driver translation unit is compiled with
 * this header force-included, which renames that API to hcd_<name>_* (e.g. hcd_dwc2_init).
 * host/hcd_multi.c then provides the standard hcd_* symbols used by usbh.c/hub.c and dispatches
 * each call by rhport through the table tuh_hcd_drivers[] supplied by the application/BSP.
 * With CFG_TUH_HCD_MULTI = 0 (default) none of this is compiled and the build is unchanged.
 *
 * Adding an HCD instance (e.g. a third driver "foo"):
 *  1. Build all sources of the driver, including helper sources that reference the hcd_* API,
 *     _hcd_data or hcd_dcache_*, with
 *        -DTUH_HCD_NAME=foo -include host/hcd_rename.h
 *     The driver sources themselves need no changes. CMake: tinyusb_hcd_multi_add() in
 *     src/CMakeLists.txt. Make: target-specific CFLAGS on those objects.
 *  2. Compile host/hcd_multi.c and set CFG_TUH_HCD_MULTI=1, CFG_TUH_HCD_MULTI_COUNT=<rhports>.
 *  3. In the BSP/application (never in src/portable):
 *        TUH_HCD_DRIVER_DEFINE(foo);
 *        hcd_driver_t const* const tuh_hcd_drivers[CFG_TUH_HCD_MULTI_COUNT] = {
 *          [0] = &hcd_dwc2_driver, [1] = &hcd_foo_driver, ...
 *        };
 *     The table is indexed by rhport; one driver may serve several rhports. Unused rhports are NULL.
 *
 * Optional ops (configure, deinit, frame_number, edpt_close, edpt_abort_xfer, edpt_clear_stall,
 * parse_full_conf_descriptor) are declared weak by TUH_HCD_DRIVER_DEFINE(); an op a driver does not
 * implement resolves to NULL in its table, and hcd_multi.c returns the same default as the weak stub
 * in usbh.c. The weak declarations live in the table TU only, so driver definitions stay strong.
 *
 * Decisions:
 *  - hcd_event_* inline helpers in hcd.h are NOT renamed: they carry rhport and route back to usbh.
 *  - hcd_dcache_clean/invalidate/clean_invalidate are always renamed per driver. They are called by
 *    drivers only (usbh.c just provides weak no-op defaults), and each driver may need a different
 *    implementation (dwc2 uses its own cache helpers).
 *  - Including this header with CFG_TUH_HCD_MULTI == 0 is an error (checked here when the macro is
 *    already visible, and again in host/hcd.h once tusb_option.h has been processed).
 *  - It must be the first thing in a driver TU (hence -include), so that the hcd.h prototypes are
 *    renamed as well.
 */

#ifndef TUSB_HCD_RENAME_H_
#define TUSB_HCD_RENAME_H_

#ifndef TUH_HCD_NAME
  #error "Define TUH_HCD_NAME (e.g. dwc2) before including host/hcd_rename.h"
#endif

#if defined(CFG_TUH_HCD_MULTI) && !CFG_TUH_HCD_MULTI
  #error "host/hcd_rename.h is only for CFG_TUH_HCD_MULTI builds"
#endif

// Self-contained concat (tusb_compiler.h is not included yet at this point).
// _TUH_HCD_XCAT(hcd, dwc2, init) -> hcd_dwc2_init
#define _TUH_HCD_CAT(_p, _n, _o)   _p##_##_n##_##_o
#define _TUH_HCD_XCAT(_p, _n, _o)  _TUH_HCD_CAT(_p, _n, _o)
#define TUH_HCD_SYM(_o)            _TUH_HCD_XCAT(hcd, TUH_HCD_NAME, _o)

// Controller
#define hcd_configure                   TUH_HCD_SYM(configure)
#define hcd_init                        TUH_HCD_SYM(init)
#define hcd_deinit                      TUH_HCD_SYM(deinit)
#define hcd_int_handler                 TUH_HCD_SYM(int_handler)
#define hcd_int_enable                  TUH_HCD_SYM(int_enable)
#define hcd_int_disable                 TUH_HCD_SYM(int_disable)
#define hcd_frame_number                TUH_HCD_SYM(frame_number)
// Port
#define hcd_port_connect_status         TUH_HCD_SYM(port_connect_status)
#define hcd_port_reset                  TUH_HCD_SYM(port_reset)
#define hcd_port_reset_end              TUH_HCD_SYM(port_reset_end)
#define hcd_port_speed_get              TUH_HCD_SYM(port_speed_get)
#define hcd_device_close                TUH_HCD_SYM(device_close)
// Endpoint
#define hcd_edpt_open                   TUH_HCD_SYM(edpt_open)
#define hcd_edpt_close                  TUH_HCD_SYM(edpt_close)
#define hcd_edpt_xfer                   TUH_HCD_SYM(edpt_xfer)
#define hcd_edpt_abort_xfer             TUH_HCD_SYM(edpt_abort_xfer)
#define hcd_setup_send                  TUH_HCD_SYM(setup_send)
#define hcd_edpt_clear_stall            TUH_HCD_SYM(edpt_clear_stall)
#define hcd_parse_full_conf_descriptor  TUH_HCD_SYM(parse_full_conf_descriptor)

// Per-driver globals that would clash
#define _hcd_data                       _TUH_HCD_XCAT(_hcd, TUH_HCD_NAME, data)
#define hcd_dcache_clean                TUH_HCD_SYM(dcache_clean)
#define hcd_dcache_invalidate           TUH_HCD_SYM(dcache_invalidate)
#define hcd_dcache_clean_invalidate     TUH_HCD_SYM(dcache_clean_invalidate)

#endif
