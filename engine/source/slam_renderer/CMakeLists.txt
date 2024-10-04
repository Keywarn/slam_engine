project(slam_renderer C CXX)
 
SET(SOURCES
    camera.h
    camera.cpp
    framebuffer.h
    framebuffer.cpp
    light.h
    light.cpp
    material.h
    material.cpp
    mesh.h
    mesh.cpp
    model.h
    model.cpp
    renderer.h
    renderer.cpp
    shader.h
    shader.cpp
    texture.h
    texture.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    slam_utils

    zlib
    assimp
    glm
    glfw
    glad
    stb_image
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine")