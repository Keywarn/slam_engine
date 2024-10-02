macro(util_setup_folder_structure name sources group)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${sources}})
    set_target_properties(${name} PROPERTIES FOLDER ${group})
endmacro()


macro(util_copy_all_dlls_to_output name)
    add_custom_command(TARGET ${name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${name}> $<TARGET_FILE_DIR:${name}>
        COMMAND_EXPAND_LISTS
    )
endmacro()

macro(util_generate_sources files)
    foreach(file ${files})
        list(APPEND SOURCES "./source/${file}.cpp")
        list(APPEND SOURCES "./include/${file}.h")
    endforeach()
endmacro()
