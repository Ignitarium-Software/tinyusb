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

// Platform glue for the generic xHCI library.
//
// The xHCI library never includes SoC/vendor headers itself. Everything platform dependent is
// obtained from the controller port that embeds the xHCI (selected by TUP_USBIP_*), which must provide:
//   - XHCI_BASE_ADDR                      : base address of the xHCI capability registers
//   - USB3_* register offsets / bit fields: xHCI register map of that controller
//   - xhci_dcache_clean(addr, size)       : write back data cache lines (void*, size_t)
//   - xhci_dcache_invalidate(addr, size)  : invalidate data cache lines (void*, size_t)
//   - XHCI_MEM_ALLOC(size), XHCI_MEM_ALLOC_ALIGNED(align, size), XHCI_MEM_ALLOC_COHERENT(size),
//     XHCI_MEM_FREE(ptr)                  : memory for rings and contexts
// Optional (generic fallbacks below): RD_REG32/WR_REG32/WR_REG64 and the INFO/DEBUG/WARN/ERROR/PRINT logs.

#ifndef XHCI_PORT_H_
#define XHCI_PORT_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "tusb_option.h"
#include "common/tusb_common.h"
#include "osal/osal.h"

#if defined(TUP_USBIP_DWC3)
  #include "portable/synopsys/dwc3/dwc3_common.h"
#else
  #error "xHCI: no controller port provides the platform glue (see xhci_port.h)"
#endif

//--------------------------------------------------------------------+
// Generic fallbacks
//--------------------------------------------------------------------+
#ifndef RD_REG32
  #define RD_REG32(_addr)        (*(volatile uint32_t const*) (uintptr_t) (_addr))
#endif

#ifndef WR_REG32
  #define WR_REG32(_addr, _val)  (*(volatile uint32_t*) (uintptr_t) (_addr) = (uint32_t) (_val))
#endif

#ifndef WR_REG64
  #define WR_REG64(_addr, _val)  (*(volatile uint64_t*) (uintptr_t) (_addr) = (uint64_t) (_val))
#endif

#ifndef ERROR
  #define ERROR(...)  TU_LOG1(__VA_ARGS__)
#endif
#ifndef WARN
  #define WARN(...)   TU_LOG1(__VA_ARGS__)
#endif
#ifndef INFO
  #define INFO(...)   TU_LOG2(__VA_ARGS__)
#endif
#ifndef DEBUG
  #define DEBUG(...)  TU_LOG3(__VA_ARGS__)
#endif
#ifndef PRINT
  #define PRINT(...)  TU_LOG1(__VA_ARGS__)
#endif

#endif
