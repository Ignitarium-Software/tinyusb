include_guard(GLOBAL)

if (DEFINED FREERTOS_TOP_DIR AND
    EXISTS "${FREERTOS_TOP_DIR}/tools/target_socfpga.cmake")
  set(SOCFPGA_SDK_SOURCE_DIR "${FREERTOS_TOP_DIR}")
else ()
  include(FetchContent)

  FetchContent_Declare(
    socfpga_sdk
    GIT_REPOSITORY https://github.com/Ignitarium-Software/freertos-socfpga.git
    GIT_TAG v26.1.1
  )

  FetchContent_GetProperties(socfpga_sdk)
  if (NOT socfpga_sdk_POPULATED)
    FetchContent_Populate(socfpga_sdk)
  endif ()

  set(SOCFPGA_SDK_SOURCE_DIR "${socfpga_sdk_SOURCE_DIR}")
  set(SOCFPGA_SDK_FETCHED TRUE)
endif ()

if (NOT DEFINED FREERTOS_TOP_DIR)
  set(FREERTOS_TOP_DIR "${SOCFPGA_SDK_SOURCE_DIR}")
endif ()

set(LINKER_SCRIPT "${SOCFPGA_SDK_SOURCE_DIR}/lscript.ld")
