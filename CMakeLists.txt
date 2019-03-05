cmake_minimum_required(VERSION 3.7)
project(LoST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2")

find_package(SDL2 REQUIRED)

include_directories("${SDL2_INCLUDE_DIRS}"
                    "${CMAKE_SOURCE_DIR}/include"
)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(LoST WIN32 ${SOURCES})
target_link_libraries(LoST ${SDL2_LIBRARIES})

if(WIN32)
    add_custom_command(TARGET LoST POST_BUILD          # Adds a post-build event to target
    COMMAND ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
        "${SDL2_DIR}/${VC_LIB_PATH_SUFFIX}/SDL2.dll"   # <--this is in-file
        $<TARGET_FILE_DIR:LoST>)                       # <--this is out-file path
endif()