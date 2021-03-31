cmake_minimum_required(VERSION 3.10)

project(n-puzzle)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/tests/main.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
