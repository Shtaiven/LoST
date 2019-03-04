cmake_minimum_required(VERSION 3.7)
project(LoST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

if(WIN32)
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2")
    message("Set SDL2_DIR to ${SDL2_DIR}")
endif()

find_package(SDL2 REQUIRED)

include_directories("${SDL2_INCLUDE_DIRS}"
                    "${CMAKE_SOURCE_DIR}/include"
)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(LoST WIN32 ${SOURCES})
target_link_libraries(LoST ${SDL2_LIBRARIES})
