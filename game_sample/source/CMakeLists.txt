project(game_sample C CXX)

include_directories("${ENV_ROOT_PATH}/engine/source")

SET(SOURCES
    "empty.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    engine
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "game_sample")

# No libs to copy yet
# util_copy_all_dlls_to_output(${PROJECT_NAME})