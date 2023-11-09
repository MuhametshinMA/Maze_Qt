cmake_minimum_required(VERSION 3.8)

project(MazeTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(${CMAKE_SOURCE_DIR}/../model)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  Maze_tests
  test_maze.cc
  test_cave.cc
)

target_link_libraries(
  Maze_tests
  GTest::gtest_main
  MazeLib
)

add_library(MazeLib SHARED
  ${CMAKE_SOURCE_DIR}/../model/maze.cc
  ${CMAKE_SOURCE_DIR}/../model/maze.h
  ${CMAKE_SOURCE_DIR}/../model/cave.cc
  ${CMAKE_SOURCE_DIR}/../model/cave.h
  ${CMAKE_SOURCE_DIR}/../model/cave_data.h
  ${CMAKE_SOURCE_DIR}/../model/checkmaze.cc
  ${CMAKE_SOURCE_DIR}/../model/checkmaze.h
  ${CMAKE_SOURCE_DIR}/../model/filemanager.cc
  ${CMAKE_SOURCE_DIR}/../model/filemanager.h
  ${CMAKE_SOURCE_DIR}/../model/generate_maze.cc
  ${CMAKE_SOURCE_DIR}/../model/position.cc
  ${CMAKE_SOURCE_DIR}/../model/position.h
  ${CMAKE_SOURCE_DIR}/../model/path.cc
  ${CMAKE_SOURCE_DIR}/../model/path.h
)

include(GoogleTest)
gtest_discover_tests(Maze_tests)
