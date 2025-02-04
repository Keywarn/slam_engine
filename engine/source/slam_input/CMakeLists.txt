project(slam_input C CXX)
 
SET(SOURCES
    input_enums.h
    input_manager.h
    input_manager.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})


target_link_libraries(${PROJECT_NAME} 
    glm

    glad
    assimp
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/input")