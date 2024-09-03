project(glad C CXX)

SET(SOURCES
    glad.h

    glad.c
    KHR/khrplatform.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")