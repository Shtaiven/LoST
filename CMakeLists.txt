cmake_minimum_required(VERSION 3.1)

project(LostGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)

add_executable(LoST src/main.cpp)
target_link_libraries(LoST ${SDL2_LIBRARIES})
