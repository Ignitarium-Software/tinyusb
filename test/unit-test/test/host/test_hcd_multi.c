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

// Unit test for host/hcd_multi.c (CFG_TUH_HCD_MULTI dispatcher).
// project.yml compiles this test with CFG_TUH_ENABLED=1, CFG_TUH_HCD_MULTI=1, CFG_TUH_HCD_MULTI_COUNT=3.

#include <string.h>
#include "unity.h"

#include "tusb_option.h"
#include "host/hcd.h"
TEST_SOURCE_FILE("hcd_multi.c")

//--------------------------------------------------------------------+
// Mock drivers
//   drv_a: implements every op
//   drv_b: required ops only (all optional ops NULL)
//--------------------------------------------------------------------+
typedef struct {
  int calls;
  uint8_t rhport;
  uint8_t daddr;
  uint8_t ep_addr;
  uint8_t* buffer;
  uint32_t buflen;
  bool in_isr;
} call_t;

static call_t call_a, call_b;

static void rec(call_t* c, uint8_t rhport) {
  c->calls++;
  c->rhport = rhport;
}

// ---- driver A
static bool a_configure(uint8_t r, uint32_t id, const void* p) { (void) id; (void) p; rec(&call_a, r); return true; }
static bool a_init(uint8_t r, const tusb_rhport_init_t* i) { (void) i; rec(&call_a, r); return true; }
static bool a_deinit(uint8_t r) { rec(&call_a, r); return true; }
static void a_int_handler(uint8_t r, bool in_isr) { rec(&call_a, r); call_a.in_isr = in_isr; }
static void a_int_enable(uint8_t r) { rec(&call_a, r); }
static void a_int_disable(uint8_t r) { rec(&call_a, r); }
static uint32_t a_frame_number(uint8_t r) { rec(&call_a, r); return 1234; }
static bool a_port_connect_status(uint8_t r) { rec(&call_a, r); return true; }
static void a_port_reset(uint8_t r) { rec(&call_a, r); }
static void a_port_reset_end(uint8_t r) { rec(&call_a, r); }
static tusb_speed_t a_port_speed_get(uint8_t r) { rec(&call_a, r); return TUSB_SPEED_HIGH; }
static void a_device_close(uint8_t r, uint8_t d) { rec(&call_a, r); call_a.daddr = d; }
static bool a_edpt_open(uint8_t r, uint8_t d, tusb_desc_endpoint_t const* e) { (void) e; rec(&call_a, r); call_a.daddr = d; return true; }
static bool a_edpt_close(uint8_t r, uint8_t d, uint8_t ep) { rec(&call_a, r); call_a.daddr = d; call_a.ep_addr = ep; return true; }
static bool a_edpt_xfer(uint8_t r, uint8_t d, uint8_t ep, uint8_t* buf, uint32_t len) {
  rec(&call_a, r); call_a.daddr = d; call_a.ep_addr = ep; call_a.buffer = buf; call_a.buflen = len; return true;
}
static bool a_edpt_abort_xfer(uint8_t r, uint8_t d, uint8_t ep) { rec(&call_a, r); call_a.daddr = d; call_a.ep_addr = ep; return true; }
static bool a_setup_send(uint8_t r, uint8_t d, uint8_t const s[8]) { (void) s; rec(&call_a, r); call_a.daddr = d; return true; }
static bool a_edpt_clear_stall(uint8_t r, uint8_t d, uint8_t ep) { rec(&call_a, r); call_a.daddr = d; call_a.ep_addr = ep; return true; }
static bool a_parse_conf(tusb_desc_configuration_t* c, uint8_t r) { (void) c; rec(&call_a, r); return false; }

// ---- driver B (required ops only)
static bool b_init(uint8_t r, const tusb_rhport_init_t* i) { (void) i; rec(&call_b, r); return true; }
static void b_int_handler(uint8_t r, bool in_isr) { rec(&call_b, r); call_b.in_isr = in_isr; }
static void b_int_enable(uint8_t r) { rec(&call_b, r); }
static void b_int_disable(uint8_t r) { rec(&call_b, r); }
static bool b_port_connect_status(uint8_t r) { rec(&call_b, r); return false; }
static void b_port_reset(uint8_t r) { rec(&call_b, r); }
static void b_port_reset_end(uint8_t r) { rec(&call_b, r); }
static tusb_speed_t b_port_speed_get(uint8_t r) { rec(&call_b, r); return TUSB_SPEED_SS; }
static void b_device_close(uint8_t r, uint8_t d) { rec(&call_b, r); call_b.daddr = d; }
static bool b_edpt_open(uint8_t r, uint8_t d, tusb_desc_endpoint_t const* e) { (void) e; rec(&call_b, r); call_b.daddr = d; return true; }
static bool b_edpt_xfer(uint8_t r, uint8_t d, uint8_t ep, uint8_t* buf, uint32_t len) {
  rec(&call_b, r); call_b.daddr = d; call_b.ep_addr = ep; call_b.buffer = buf; call_b.buflen = len; return true;
}
static bool b_setup_send(uint8_t r, uint8_t d, uint8_t const s[8]) { (void) s; rec(&call_b, r); call_b.daddr = d; return true; }

static hcd_driver_t const drv_a = {
  .name = "a",
  .configure = a_configure, .init = a_init, .deinit = a_deinit,
  .int_handler = a_int_handler, .int_enable = a_int_enable, .int_disable = a_int_disable,
  .frame_number = a_frame_number,
  .port_connect_status = a_port_connect_status, .port_reset = a_port_reset, .port_reset_end = a_port_reset_end,
  .port_speed_get = a_port_speed_get, .device_close = a_device_close,
  .edpt_open = a_edpt_open, .edpt_close = a_edpt_close, .edpt_xfer = a_edpt_xfer,
  .edpt_abort_xfer = a_edpt_abort_xfer, .setup_send = a_setup_send, .edpt_clear_stall = a_edpt_clear_stall,
  .parse_full_conf_descriptor = a_parse_conf,
};

static hcd_driver_t const drv_b = {
  .name = "b",
  .init = b_init,
  .int_handler = b_int_handler, .int_enable = b_int_enable, .int_disable = b_int_disable,
  .port_connect_status = b_port_connect_status, .port_reset = b_port_reset, .port_reset_end = b_port_reset_end,
  .port_speed_get = b_port_speed_get, .device_close = b_device_close,
  .edpt_open = b_edpt_open, .edpt_xfer = b_edpt_xfer, .setup_send = b_setup_send,
};

// rhport 0 -> A, rhport 1 -> B, rhport 2 -> no driver
hcd_driver_t const* const tuh_hcd_drivers[CFG_TUH_HCD_MULTI_COUNT] = { &drv_a, &drv_b, NULL };

void setUp(void) {
  memset(&call_a, 0, sizeof(call_a));
  memset(&call_b, 0, sizeof(call_b));
}

void tearDown(void) {
}

//--------------------------------------------------------------------+
// Routing by rhport
//--------------------------------------------------------------------+
void test_route_init_by_rhport(void) {
  tusb_rhport_init_t rh_init = { .role = TUSB_ROLE_HOST, .speed = TUSB_SPEED_AUTO };

  TEST_ASSERT_TRUE(hcd_init(0, &rh_init));
  TEST_ASSERT_EQUAL(1, call_a.calls);
  TEST_ASSERT_EQUAL(0, call_a.rhport);
  TEST_ASSERT_EQUAL(0, call_b.calls);

  TEST_ASSERT_TRUE(hcd_init(1, &rh_init));
  TEST_ASSERT_EQUAL(1, call_b.calls);
  TEST_ASSERT_EQUAL(1, call_b.rhport);
  TEST_ASSERT_EQUAL(1, call_a.calls);
}

void test_route_int_handler_keeps_in_isr(void) {
  hcd_int_handler(1, true);
  TEST_ASSERT_EQUAL(1, call_b.calls);
  TEST_ASSERT_TRUE(call_b.in_isr);
  TEST_ASSERT_EQUAL(0, call_a.calls);

  hcd_int_handler(0, false);
  TEST_ASSERT_EQUAL(1, call_a.calls);
  TEST_ASSERT_FALSE(call_a.in_isr);
}

void test_route_port_ops(void) {
  TEST_ASSERT_TRUE(hcd_port_connect_status(0));
  TEST_ASSERT_FALSE(hcd_port_connect_status(1));
  TEST_ASSERT_EQUAL(TUSB_SPEED_HIGH, hcd_port_speed_get(0));
  TEST_ASSERT_EQUAL(TUSB_SPEED_SS, hcd_port_speed_get(1));

  hcd_port_reset(1);
  hcd_port_reset_end(1);
  hcd_int_enable(1);
  hcd_int_disable(1);
  TEST_ASSERT_EQUAL(6, call_b.calls);
  TEST_ASSERT_EQUAL(2, call_a.calls);
}

void test_route_xfer_arguments(void) {
  uint8_t buf[16];
  TEST_ASSERT_TRUE(hcd_edpt_xfer(1, 5, 0x81, buf, 70000));
  TEST_ASSERT_EQUAL(1, call_b.calls);
  TEST_ASSERT_EQUAL(1, call_b.rhport);
  TEST_ASSERT_EQUAL(5, call_b.daddr);
  TEST_ASSERT_EQUAL_HEX8(0x81, call_b.ep_addr);
  TEST_ASSERT_EQUAL_PTR(buf, call_b.buffer);
  TEST_ASSERT_EQUAL_UINT32(70000, call_b.buflen); // uint32_t length must not be truncated
  TEST_ASSERT_EQUAL(0, call_a.calls);

  hcd_device_close(0, 3);
  TEST_ASSERT_EQUAL(1, call_a.calls);
  TEST_ASSERT_EQUAL(3, call_a.daddr);
}

void test_optional_ops_present(void) {
  TEST_ASSERT_TRUE(hcd_configure(0, 0, NULL));
  TEST_ASSERT_TRUE(hcd_deinit(0));
  TEST_ASSERT_EQUAL_UINT32(1234, hcd_frame_number(0));
  TEST_ASSERT_TRUE(hcd_edpt_close(0, 1, 0x02));
  TEST_ASSERT_TRUE(hcd_edpt_abort_xfer(0, 1, 0x02));
  TEST_ASSERT_TRUE(hcd_edpt_clear_stall(0, 1, 0x02));
  TEST_ASSERT_FALSE(hcd_parse_full_conf_descriptor(NULL, 0)); // value returned by driver A
  TEST_ASSERT_EQUAL(7, call_a.calls);
}

//--------------------------------------------------------------------+
// NULL optional ops: same defaults as the weak stubs in usbh.c
//--------------------------------------------------------------------+
void test_optional_ops_null_defaults(void) {
  TEST_ASSERT_FALSE(hcd_configure(1, 0, NULL));
  TEST_ASSERT_FALSE(hcd_deinit(1));
  TEST_ASSERT_EQUAL_UINT32(0, hcd_frame_number(1));
  TEST_ASSERT_FALSE(hcd_edpt_close(1, 1, 0x02));
  TEST_ASSERT_FALSE(hcd_edpt_abort_xfer(1, 1, 0x02));
  TEST_ASSERT_FALSE(hcd_edpt_clear_stall(1, 1, 0x02));
  TEST_ASSERT_TRUE(hcd_parse_full_conf_descriptor(NULL, 1));
  TEST_ASSERT_EQUAL(0, call_b.calls);
  TEST_ASSERT_EQUAL(0, call_a.calls);
}

//--------------------------------------------------------------------+
// Invalid rhport: assert path returns a safe value and calls nothing
//--------------------------------------------------------------------+
void test_invalid_rhport(void) {
  tusb_rhport_init_t rh_init = { .role = TUSB_ROLE_HOST, .speed = TUSB_SPEED_AUTO };
  uint8_t buf[4];
  uint8_t const setup[8] = { 0 };

  // rhport 2: entry is NULL, rhport 7: beyond the table
  for (uint8_t r = 2; r <= 7; r += 5) {
    TEST_ASSERT_FALSE(hcd_init(r, &rh_init));
    TEST_ASSERT_FALSE(hcd_edpt_xfer(r, 1, 0x81, buf, sizeof(buf)));
    TEST_ASSERT_FALSE(hcd_setup_send(r, 1, setup));
    TEST_ASSERT_FALSE(hcd_port_connect_status(r));
    TEST_ASSERT_EQUAL(TUSB_SPEED_INVALID, hcd_port_speed_get(r));
    TEST_ASSERT_EQUAL_UINT32(0, hcd_frame_number(r));
    TEST_ASSERT_FALSE(hcd_parse_full_conf_descriptor(NULL, r));
    hcd_int_handler(r, true);
    hcd_int_enable(r);
    hcd_device_close(r, 1);
  }

  TEST_ASSERT_EQUAL(0, call_a.calls);
  TEST_ASSERT_EQUAL(0, call_b.calls);
}
