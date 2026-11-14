include_guard()

# ----------------------
# Port & Speed Selection
# ----------------------
if (NOT DEFINED RHPORT_DEVICE)
  set(RHPORT_DEVICE 0)
endif ()
if (NOT DEFINED RHPORT_HOST)
  set(RHPORT_HOST 0)
endif ()

set(RHPORT_DEVICE_SPEED OPT_MODE_HIGH_SPEED)

# ----------------------
# Host controller selection
#   dwc2 : USB2.0 OTG (DWC2), rhport 0
#   dwc3 : USB3.1 (DWC3 in xHCI host mode), rhports 1 (USB2 port) and 2 (USB3 port)
# Each value builds exactly one standard TinyUSB HCD.
# ----------------------
set(SOCFPGA_HCD "dwc3" CACHE STRING "SoC FPGA host controller driver: dwc2 or dwc3")
set_property(CACHE SOCFPGA_HCD PROPERTY STRINGS dwc2 dwc3)
option(SOCFPGA_HCD_WERROR "Build the TinyUSB library with -Wall -Wextra -Werror" OFF)

set(TUSB_SRC ${FREERTOS_TOP_DIR}/tinyusb/src)

if (SOCFPGA_HCD STREQUAL "dwc2")
  set(SOCFPGA_HCD_DWC2 1)
  set(SOCFPGA_HCD_DWC3 0)
elseif (SOCFPGA_HCD STREQUAL "dwc3")
  set(SOCFPGA_HCD_DWC2 0)
  set(SOCFPGA_HCD_DWC3 1)
else ()
  message(FATAL_ERROR "SOCFPGA_HCD must be dwc2 or dwc3 (got '${SOCFPGA_HCD}')")
endif ()
message(STATUS "SoC FPGA TinyUSB HCD : ${SOCFPGA_HCD}")

add_subdirectory(${TUSB_SRC} ${CMAKE_CURRENT_BINARY_DIR}/tinyusb)

add_library(agilex5-tinyusb STATIC)

target_compile_definitions(agilex5-tinyusb PUBLIC
  CFG_TUSB_MCU=OPT_MCU_SOCFPGA
  CFG_TUSB_OS=OPT_OS_FREERTOS
  BOARD_TUH_MAX_SPEED=${RHPORT_DEVICE_SPEED}
  SOCFPGA_HCD_DWC2=${SOCFPGA_HCD_DWC2}
  SOCFPGA_HCD_DWC3=${SOCFPGA_HCD_DWC3}
  )

target_include_directories(agilex5-tinyusb PUBLIC
  ${FREERTOS_TOP_DIR}/drivers/usb_otg
  ${TUSB_SRC}/class/msc
  ${TUSB_SRC}/common
  ${FREERTOS_TOP_DIR}/tinyusb/apps/
  )

# Add TinyUSB target and port source
tinyusb_target_add(agilex5-tinyusb)

if (SOCFPGA_HCD_DWC2)
  target_include_directories(agilex5-tinyusb PUBLIC ${TUSB_SRC}/portable/synopsys/dwc2)
  target_sources(agilex5-tinyusb PRIVATE
    ${TUSB_SRC}/portable/synopsys/dwc2/hcd_dwc2.c
    ${TUSB_SRC}/portable/synopsys/dwc2/dwc2_common.c
    )
endif ()

if (SOCFPGA_HCD_DWC3)
  target_include_directories(agilex5-tinyusb PUBLIC
    ${TUSB_SRC}/portable/synopsys/dwc3
    ${TUSB_SRC}/portable/xhci
    )
  target_sources(agilex5-tinyusb PRIVATE
    ${TUSB_SRC}/portable/synopsys/dwc3/hcd_dwc3.c
    ${TUSB_SRC}/portable/synopsys/dwc3/dwc3_common.c
    ${TUSB_SRC}/portable/xhci/xhci.c
    ${TUSB_SRC}/portable/xhci/xhci_cap.c
    ${TUSB_SRC}/portable/xhci/xhci_commands.c
    ${TUSB_SRC}/portable/xhci/xhci_context.c
    ${TUSB_SRC}/portable/xhci/xhci_doorbell.c
    ${TUSB_SRC}/portable/xhci/xhci_endpoints.c
    ${TUSB_SRC}/portable/xhci/xhci_events.c
    ${TUSB_SRC}/portable/xhci/xhci_interrupts.c
    ${TUSB_SRC}/portable/xhci/xhci_rings.c
    )
endif ()

if (SOCFPGA_HCD_WERROR)
  target_compile_options(agilex5-tinyusb PRIVATE -Wall -Wextra -Werror)
endif ()

target_link_libraries(agilex5-tinyusb PRIVATE socfpga_drivers m)
