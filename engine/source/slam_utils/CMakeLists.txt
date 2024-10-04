project(slam_utils C CXX)
 
SET(SOURCES
    patterns/singleton.h
    patterns/singleton.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine")