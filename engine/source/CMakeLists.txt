include_directories(./)

add_subdirectory(./slam_main)
add_subdirectory(./slam_main.windows)
add_subdirectory(./slam_utils)

add_subdirectory(./slam_ecs)

add_subdirectory(./slam_window)
add_subdirectory(./slam_window.glfw)
add_subdirectory(./slam_input)
add_subdirectory(./slam_input.glfw)

add_subdirectory(./slam_renderer)

add_subdirectory(./thirdparty)
