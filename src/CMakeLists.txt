cmake_minimum_required(VERSION 3.20)

# Add tinyusb to a existing target, DCD and HCD drivers are not included
function(tinyusb_target_add TARGET)
  target_sources(${TARGET} PRIVATE
    # common
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/tusb.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/common/tusb_fifo.c
    # device
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/device/usbd.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/device/usbd_control.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/audio/audio_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/cdc/cdc_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/dfu/dfu_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/dfu/dfu_rt_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/hid/hid_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/midi/midi_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/msc/msc_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/mtp/mtp_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/net/ecm_rndis_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/net/ncm_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/usbtmc/usbtmc_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/vendor/vendor_device.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/video/video_device.c
    # host
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/host/usbh.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/host/hub.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/host/hcd_multi.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/cdc/cdc_host.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/hid/hid_host.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/midi/midi_host.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/msc/msc_host.c
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/class/vendor/vendor_host.c
    # typec
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/typec/usbc.c
    )
  target_include_directories(${TARGET} PUBLIC
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}
    # TODO for net driver, should be removed/changed
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../lib/networking
    )
endfunction()

# CFG_TUH_HCD_MULTI: add the sources of one host controller driver instance to TARGET, compiled with
# TUH_HCD_NAME=<NAME> and host/hcd_rename.h force-included (renames its hcd_* API to hcd_<NAME>_*).
# Pass every source of the driver, including helper sources. See src/host/hcd_rename.h.
#   tinyusb_hcd_multi_add(<TARGET> <NAME> <source>...)
function(tinyusb_hcd_multi_add TARGET NAME)
  set(_srcs ${ARGN})
  target_sources(${TARGET} PRIVATE ${_srcs})
  set_property(SOURCE ${_srcs} APPEND PROPERTY COMPILE_DEFINITIONS TUH_HCD_NAME=${NAME})
  set_property(SOURCE ${_srcs} APPEND PROPERTY COMPILE_OPTIONS
    -include ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/host/hcd_rename.h)
endfunction()
