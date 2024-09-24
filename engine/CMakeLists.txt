project(engine C CXX)

add_subdirectory(source/thirdparty)
 
SET(SOURCES
    "./source/camera.cpp"
    "./source/framebuffer.cpp"
    "./source/light.cpp"
    "./source/main.cpp"
    "./source/material.cpp"
    "./source/mesh.cpp"
    "./source/model.cpp"
    "./source/renderer.cpp"
    "./source/shader.cpp"
    "./source/singleton.cpp"
    "./source/texture.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
    zlib
    assimp
    glm
    glfw
    glad
    stb_image
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine")