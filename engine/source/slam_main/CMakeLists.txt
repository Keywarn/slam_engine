project(slam_main C CXX)
 
SET(SOURCES
    entry.h
    entry.cpp
    ./game/game.h
    ./game/game.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    slam_renderer
    slam_main.windows
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/main")