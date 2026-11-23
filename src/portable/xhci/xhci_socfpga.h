#ifndef XHCI_SOCFGPA_H_
#define XHCI_SOCFPGA_H_

#ifdef __cplusplus
extern "C" {
#endif

#if CFG_TUSB_MCU == OPT_MCU_SOCFPGA
  #define USB3_IRQn               126 // IRQ num for USB1 = 126
  #include "tusb.h"
  #include "socfpga_interrupt.h"
  #include "socfpga_interrupt_priority.h"
  #include "xhci_events.h"
  #include "xhci_commands.h"
  #include "xhci_endpoints.h"
  #include "xhci_doorbell.h"
#endif

static void usb3_isr(void *arg)
{
  (void) arg;
  tusb_int_handler(1, true);
}

TU_ATTR_ALWAYS_INLINE static bool inline register_usb3ISR()
{
    int err;

    err = interrupt_register_isr(USB3_IRQn, usb3_isr, NULL);
    if (err != 0)
    {
        return false;
    }

    err = interrupt_enable(USB3_IRQn, GIC_INTERRUPT_PRIORITY_USB3);
    if (err != 0)
    {
        return false;
    }

    return true;
}

#ifdef __cplusplus
}
#endif

#endif
