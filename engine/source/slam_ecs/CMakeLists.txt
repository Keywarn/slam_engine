project(slam_ecs C CXX)
 
SET(SOURCES
    component.h
    system.h
    scene.h
    scene.cpp
    component_pool.h
    
    ./components/transform_component.h
    ./systems/transform_system.h
    ./systems/transform_system.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    glm
)

util_setup_folder_structure(${PROJECT_NAME} SOURCES "engine/ecs")