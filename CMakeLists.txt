cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)
project(LoST)

# Must be set to find SDL2 on Windows
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2")

# Must be set to copy DLLs to build directory
set(COPY_DLLS TRUE)

add_subdirectory(LGE)
add_subdirectory(${CMAKE_PROJECT_NAME})
