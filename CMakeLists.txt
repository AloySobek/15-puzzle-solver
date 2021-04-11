cmake_minimum_required(VERSION 3.10)

project(n-puzzle)

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/parser.cpp
    ${PROJECT_SOURCE_DIR}/src/solver.cpp
    ${PROJECT_SOURCE_DIR}/src/heuristics.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${Boost_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME}
    LINK_PUBLIC
    ${Boost_LIBRARIES}
)
