project(game_sample C CXX)

SET(SOURCES
 "empty.cpp"
)
 
add_library(${PROJECT_NAME} STATIC ${SOURCES})

util_setup_folder_structure(${PROJECT_NAME} SOURCES "game_sample")