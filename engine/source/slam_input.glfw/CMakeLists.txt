project(slam_input.glfw C CXX)
 
SET(SOURCES
    input_manager_glfw.h
    input_manager_glfw.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    slam_input
    glfw
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/input")