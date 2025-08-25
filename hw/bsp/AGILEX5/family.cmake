set(TINYUSB_TARGET_PREFIX "agilex5-")

set(MCU_AGILEX5 2500) #Custom value for CFG_TUSB_MCU
set(OPT_MCU_AGILEX5 ${MCU_AGILEX5})

add_library(agilex5-tinyusb_config  INTERFACE)

#define the path to tusb_config.h
target_include_directories(agilex5-tinyusb_config
    INTERFACE
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/socfpga/
    ${FREERTOS_TOP_DIR}/tinyusb/src/class/msc/
    ${FREERTOS_TOP_DIR}/FreeRTOS/FreeRTOS-Plus/Source/Utilities/logging/
)

target_compile_definitions(agilex5-tinyusb_config INTERFACE CFG_TUSB_MCU=${OPT_MCU_AGILEX5} TUP_DCD_ENDPOINT_MAX=1)
add_subdirectory(${FREERTOS_TOP_DIR}/tinyusb/src ${CMAKE_CURRENT_BINARY_DIR}/tinyusb)

target_sources(agilex5-tinyusb
    PUBLIC
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/synopsys/dwc2/hcd_dwc2.c
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/socfpga/socfpga_common.c
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/socfpga/msc_app.c
    ${FREERTOS_TOP_DIR}/tinyusb/src/portable/socfpga/usb_main.c
)

target_compile_options(agilex5-tinyusb  PRIVATE "-Wno-error=missing-prototypes" "-Wno-missing-prototypes" "-Wno-redundant-decls" "-Wno-error=redundant-decls"  "-Wno-error=shadow" "-Wno-shadow" "-Wno-error=cast-qual" "-Wno-cast-qual"  "-Wno-error=strict-prototypes" "-Wno-strict-prototypes")

#Link freertos kernel and drivers to tinyusb
target_link_libraries(agilex5-tinyusb PRIVATE m freertos_kernel socfpga_drivers)
