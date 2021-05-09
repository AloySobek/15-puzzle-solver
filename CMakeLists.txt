cmake_minimum_required(VERSION 3.10)

project(n-puzzle)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra")
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/parser.cpp
    ${PROJECT_SOURCE_DIR}/src/solver.cpp
    ${PROJECT_SOURCE_DIR}/src/state.cpp
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
