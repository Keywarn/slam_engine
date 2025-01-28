project(slam_input C CXX)
 
SET(SOURCES
    input_manager.h
    input_manager.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/input")