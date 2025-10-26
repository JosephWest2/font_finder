cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

set(PROJECT_NAME font_finder)

project(${PROJECT_NAME} VERSION 0.1)

file (GLOB_RECURSE 
    SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE src
)

add_executable(${PROJECT_NAME}_test src/finder_test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
