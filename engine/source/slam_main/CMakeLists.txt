project(slam_main C CXX)
 
SET(SOURCES
    main.h
    main.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    slam_renderer
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine")