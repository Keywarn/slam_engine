add_subdirectory(zlib)
util_setup_folder_structure(zlib SOURCES "engine/thirdparty")

add_subdirectory(assimp)
util_setup_folder_structure(assimp SOURCES "engine/thirdparty")

add_subdirectory(glfw)
util_setup_folder_structure(glfw SOURCES "engine/thirdparty")

add_subdirectory(glm)
util_setup_folder_structure(glm SOURCES "engine/thirdparty")

add_subdirectory(glad)
util_setup_folder_structure(glad SOURCES "engine/thirdparty")

add_subdirectory(stb_image)
util_setup_folder_structure(stb_image SOURCES "engine/thirdparty")
