#include "bsp/board_api.h"
#include "socfpga_console.h"
#include "socfpga_interrupt.h"

#include "FreeRTOSConfig.h"

void board_init(void) {
  interrupt_init_gic();
  (void) console_init(configCONSOLE_UART_ID, "115200-8N1");
}

void board_init_after_tusb(void) {}

void board_led_write(bool state) {
  (void) state;
}

uint32_t board_button_read(void) {
  return 0;
}

int board_uart_read(uint8_t *buf, int len) {
  int result = console_read(buf, len);
  return result > 0 ? result : 0;
}

int board_uart_write(void const *buf, int len) {
  return console_write((unsigned char *)(uintptr_t) buf, len);
}

int board_getchar(void) {
  uint8_t ch;
  return board_uart_read(&ch, 1) == 1 ? ch : -1;
}

void board_putchar(int c) {
  uint8_t ch = (uint8_t) c;
  (void) board_uart_write(&ch, 1);
}

uint32_t tusb_time_millis_api(void) {
  return board_millis();
}

void vApplicationMallocFailedHook(void) {
  taskDISABLE_INTERRUPTS();
  for (;;) {}
}

void vApplicationIdleHook(void) {}

void vApplicationTickHook(void) {}

#if CFG_TUSB_OS == OPT_OS_NONE
uint32_t board_millis(void) {
  uint64_t counter;
  uint64_t frequency;
  __asm volatile("mrs %0, cntpct_el0" : "=r"(counter));
  __asm volatile("mrs %0, cntfrq_el0" : "=r"(frequency));
  return frequency ? (uint32_t) ((counter * 1000U) / frequency) : 0;
}
#endif
