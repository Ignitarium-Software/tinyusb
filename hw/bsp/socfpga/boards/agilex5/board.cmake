set(MCU_VARIANT agilex5)
#set(JLINK_DEVICE )

set(LD_FILE_GNU ${CMAKE_CURRENT_LIST_DIR}/agilex5.ld)

function(update_board TARGET)
  target_compile_definitions(${TARGET} PUBLIC
    AGILEX5
    )
endfunction()
