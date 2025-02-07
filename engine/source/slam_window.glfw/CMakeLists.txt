project(slam_window.glfw C CXX)
 
SET(SOURCES
    window_glfw.h
    window_glfw.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    slam_window

    glad
    glfw
    glm
    assimp
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/window")