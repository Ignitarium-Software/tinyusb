include_guard(GLOBAL)

if (NOT BOARD)
  set(BOARD agilex5)
endif ()

include(${CMAKE_CURRENT_LIST_DIR}/boards/${BOARD}/board.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/socfpga_sdk_import.cmake)

if (SOCFPGA_SDK_FETCHED)
  if (NOT DEFINED SOC)
    set(SOC AGILEX5)
  endif ()
  if (NOT DEFINED CORE)
    set(CORE A55)
  endif ()
  include(${SOCFPGA_SDK_SOURCE_DIR}/tools/target_socfpga.cmake)
  set(FREERTOS_CONFIG_HEADER_PATH
    ${SOCFPGA_SDK_SOURCE_DIR}/FreeRTOS/Demo/SOCFPGA)

  foreach(LANGUAGE C CXX ASM)
    find_program(SOCFPGA_${LANGUAGE}_COMPILER_PATH
      NAMES ${CMAKE_${LANGUAGE}_COMPILER})
    if (NOT SOCFPGA_${LANGUAGE}_COMPILER_PATH)
      message(FATAL_ERROR
        "Could not find SoCFPGA ${LANGUAGE} compiler: ${CMAKE_${LANGUAGE}_COMPILER}")
    endif ()
    set(CMAKE_${LANGUAGE}_COMPILER "${SOCFPGA_${LANGUAGE}_COMPILER_PATH}"
      CACHE FILEPATH "" FORCE)
  endforeach ()
endif ()

set(FAMILY_MCUS AGILEX5)

if (NOT DEFINED RHPORT_DEVICE)
  set(RHPORT_DEVICE 0)
endif ()
if (NOT DEFINED RHPORT_HOST)
  set(RHPORT_HOST 0)
endif ()

if (NOT DEFINED RHPORT_DEVICE_SPEED)
  set(RHPORT_DEVICE_SPEED OPT_MODE_HIGH_SPEED)
endif ()
if (NOT DEFINED RHPORT_HOST_SPEED)
  set(RHPORT_HOST_SPEED OPT_MODE_HIGH_SPEED)
endif ()

set(SOCFPGA_HCD "both" CACHE STRING "SoC FPGA host controller driver: dwc2, dwc3 or both")
set_property(CACHE SOCFPGA_HCD PROPERTY STRINGS dwc2 dwc3 both)
option(SOCFPGA_HCD_WERROR "Build the TinyUSB library with -Wall -Wextra -Werror" OFF)

if (SOCFPGA_HCD STREQUAL "dwc2")
  set(SOCFPGA_HCD_DWC2 1)
  set(SOCFPGA_HCD_DWC3 0)
elseif (SOCFPGA_HCD STREQUAL "dwc3")
  set(SOCFPGA_HCD_DWC2 0)
  set(SOCFPGA_HCD_DWC3 1)
elseif (SOCFPGA_HCD STREQUAL "both")
  set(SOCFPGA_HCD_DWC2 1)
  set(SOCFPGA_HCD_DWC3 1)
else ()
  message(FATAL_ERROR "SOCFPGA_HCD must be dwc2, dwc3 or both (got '${SOCFPGA_HCD}')")
endif ()
message(STATUS "SoC FPGA TinyUSB HCD: ${SOCFPGA_HCD}")

get_filename_component(TINYUSB_TOP "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

function(socfpga_add_hcd_sources TARGET)
  target_compile_definitions(${TARGET} PUBLIC
    BOARD_TUD_MAX_SPEED=${RHPORT_DEVICE_SPEED}
    BOARD_TUH_MAX_SPEED=${RHPORT_HOST_SPEED}
    SOCFPGA_HCD_DWC2=${SOCFPGA_HCD_DWC2}
    SOCFPGA_HCD_DWC3=${SOCFPGA_HCD_DWC3}
  )

  set(SOCFPGA_DWC2_SRCS
    ${TINYUSB_TOP}/src/portable/synopsys/dwc2/hcd_dwc2.c
    ${TINYUSB_TOP}/src/portable/synopsys/dwc2/dwc2_common.c
  )

  set(SOCFPGA_DWC3_SRCS
    ${TINYUSB_TOP}/src/portable/synopsys/dwc3/hcd_dwc3.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_common.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_cap.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_commands.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_context.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_doorbell.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_endpoints.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_events.c
    ${TINYUSB_TOP}/src/portable/xhci/xhci_rings.c
  )

  if (SOCFPGA_HCD STREQUAL "both")
    target_compile_definitions(${TARGET} PUBLIC
      CFG_TUH_HCD_MULTI=1
      CFG_TUH_HCD_MULTI_COUNT=3
    )
    tinyusb_hcd_multi_add(${TARGET} dwc2 ${SOCFPGA_DWC2_SRCS})
    tinyusb_hcd_multi_add(${TARGET} dwc3 ${SOCFPGA_DWC3_SRCS})
    target_sources(${TARGET} PRIVATE
      ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/hcd_socfpga_multi.c
      ${TINYUSB_TOP}/src/host/hcd_multi.c
    )
  elseif (SOCFPGA_HCD STREQUAL "dwc2")
    target_sources(${TARGET} PRIVATE ${SOCFPGA_DWC2_SRCS})
  else ()
    target_sources(${TARGET} PRIVATE ${SOCFPGA_DWC3_SRCS})
  endif ()

  if (SOCFPGA_HCD_WERROR)
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Werror)
  endif ()
endfunction()

function(socfpga_add_sdk)
  if (TARGET socfpga_drivers)
    return()
  endif ()

  if (NOT SOCFPGA_SDK_FETCHED)
    message(FATAL_ERROR
      "The Agilex 5 TinyUSB target requires the SoCFPGA SDK build "
      "(socfpga_drivers target).")
  endif ()

  if (NOT SOF_PATH)
    set(SOF_PATH "${SOCFPGA_SDK_SOURCE_DIR}/agilex5.sof")
  endif ()
  set(FREERTOS_FATFS OFF)

  add_library(freertos_socfpga STATIC
    ${SOCFPGA_SDK_SOURCE_DIR}/FreeRTOS/portable/GCC/ARM_AARCH64/portStandardLib.c)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(freertos_socfpga PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
  else ()
    target_compile_options(freertos_socfpga PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
  endif ()

  add_subdirectory(${SOCFPGA_SDK_SOURCE_DIR}/FreeRTOS
    ${CMAKE_BINARY_DIR}/socfpga-sdk/FreeRTOS)
  add_subdirectory(${SOCFPGA_SDK_SOURCE_DIR}/drivers
    ${CMAKE_BINARY_DIR}/socfpga-sdk/drivers)

  get_property(SOCFPGA_DRIVER_INCLUDE_DIRS
    TARGET socfpga_drivers PROPERTY INCLUDE_DIRECTORIES)
  target_include_directories(freertos_socfpga PUBLIC
    ${SOCFPGA_DRIVER_INCLUDE_DIRS})
  target_sources(freertos_socfpga PRIVATE
    $<TARGET_OBJECTS:socfpga_drivers>)
  target_link_libraries(freertos_socfpga PUBLIC freertos_kernel)
endfunction()

if (TARGET socfpga_drivers)
  add_subdirectory(${TINYUSB_TOP}/src ${CMAKE_CURRENT_BINARY_DIR}/tinyusb)
  add_library(agilex5-tinyusb STATIC)
  target_compile_definitions(agilex5-tinyusb PUBLIC
    CFG_TUSB_MCU=OPT_MCU_SOCFPGA
    CFG_TUSB_OS=OPT_OS_FREERTOS
  )
  target_include_directories(agilex5-tinyusb PUBLIC
    ${FREERTOS_TOP_DIR}/drivers/usb_otg
    ${TINYUSB_TOP}/src
    ${TINYUSB_TOP}/src/class/msc
    ${TINYUSB_TOP}/src/common
    ${TINYUSB_TOP}/apps
    ${TINYUSB_TOP}/src/portable/synopsys/dwc3
    ${TINYUSB_TOP}/src/portable/synopsys/dwc2
    ${TINYUSB_TOP}/src/portable/xhci
  )
  tinyusb_target_add(agilex5-tinyusb)
  socfpga_add_hcd_sources(agilex5-tinyusb)
  target_link_libraries(agilex5-tinyusb PRIVATE socfpga_drivers m)
endif ()

function(family_configure_host_example TARGET RTOS)
  socfpga_add_sdk()
  family_configure_common(${TARGET} ${RTOS})

  target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/family.c
    ${SOCFPGA_SDK_SOURCE_DIR}/FreeRTOS/portable/GCC/ARM_AARCH64/portStandardLib.c
  )
  target_include_directories(${TARGET} PUBLIC
    ${TINYUSB_TOP}/hw
    ${TINYUSB_TOP}/src/common
    ${TINYUSB_TOP}/src/class/msc
    ${TINYUSB_TOP}/apps
    ${TINYUSB_TOP}/src/portable/xhci
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/boards/${BOARD}
  )
  target_compile_definitions(${TARGET} PUBLIC
    CFG_TUSB_MCU=OPT_MCU_SOCFPGA
    CFG_TUSB_OS=OPT_OS_FREERTOS
    BOARD_TUH_RHPORT=${RHPORT_HOST}
    SOCFPGA_USB3_HS_PORT=1
    SOCFPGA_USB3_SS_PORT=2
  )

  family_add_tinyusb(${TARGET} OPT_MCU_SOCFPGA)
  socfpga_add_hcd_sources(${TARGET})
  target_link_libraries(${TARGET} PUBLIC
    freertos_socfpga
    freertos_kernel
    socfpga_drivers
    m
  )
  target_link_options(${TARGET} PRIVATE
    "LINKER:--script=${LD_FILE_GNU}"
  )

  family_add_bin_hex(${TARGET})
endfunction()
