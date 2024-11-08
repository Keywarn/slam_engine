project(slam_main.windows C CXX)
 
SET(SOURCES
    entry.cpp
    entry.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    slam_main
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/main")