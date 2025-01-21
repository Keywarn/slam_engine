project(slam_window C CXX)
 
SET(SOURCES
    window.h
    window.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/window")