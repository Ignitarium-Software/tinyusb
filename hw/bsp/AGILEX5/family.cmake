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

add_subdirectory(${FREERTOS_TOP_DIR}/tinyusb/src ${CMAKE_CURRENT_BINARY_DIR}/tinyusb)

add_library(agilex5-tinyusb STATIC)

target_compile_definitions(agilex5-tinyusb PUBLIC CFG_TUSB_MCU=OPT_MCU_SOCFPGA CFG_TUSB_OS=OPT_OS_FREERTOS BOARD_TUH_MAX_SPEED=${RHPORT_DEVICE_SPEED} CFG_TUH_DWC2_DMA_ENABLE=0)

target_include_directories(agilex5-tinyusb PUBLIC
  ${FREERTOS_TOP_DIR}/samples/usb_otg
  ${FREERTOS_TOP_DIR}/drivers/usb_otg
  ${FREERTOS_TOP_DIR}/tinyusb/src/class/msc
  )

# Add TinyUSB target and port source
  tinyusb_target_add(agilex5-tinyusb)

  target_sources(agilex5-tinyusb PUBLIC
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/synopsys/dwc2/hcd_dwc2.c
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/synopsys/dwc2/dwc2_common.c
    )
target_link_libraries(agilex5-tinyusb PRIVATE socfpga_drivers)

#target_compile_options(agilex5-tinyusb  PRIVATE "-Wno-error=unused-variable")
