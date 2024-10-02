project(engine C CXX)

add_subdirectory(source/thirdparty)
 
SET(FILES
    camera
    framebuffer
    light
    main
    material
    mesh
    model
    renderer
    shader
    singleton
    texture
)

util_generate_sources("${FILES}")

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