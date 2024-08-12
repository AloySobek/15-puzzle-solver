cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0167 NEW)

project(15-puzzle-solver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(
  Boost
  COMPONENTS program_options
  REQUIRED)

add_executable(
  ${PROJECT_NAME}
  ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/parser.cpp
  ${PROJECT_SOURCE_DIR}/src/solver.cpp ${PROJECT_SOURCE_DIR}/src/state.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR}
                                                   ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
