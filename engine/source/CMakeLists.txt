project(engine C CXX)

add_subdirectory(thirdparty)

SET(SOURCES
    "camera.cpp"
    "camera.h"
    "framebuffer.cpp"
    "framebuffer.h"
    "light.cpp"
    "light.h"
    "main.cpp"
    "material.cpp"
    "material.h"
    "mesh.cpp"
    "mesh.h"
    "model.cpp"
    "model.h"
    "renderer.cpp"
    "renderer.h"
    "shader.cpp"
    "shader.h"
    "singleton.cpp"
    "singleton.h"
    "texture.cpp"
    "texture.h"
)
 
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    assimp
    glm
    glfw
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine")