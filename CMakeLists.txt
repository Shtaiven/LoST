cmake_minimum_required(VERSION 3.7)
project(LoST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#Must be set to find SDL2 on Windows
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories("${SDL2_INCLUDE_DIRS}"
                    "${SDL2_IMAGE_INCLUDE_DIRS}"
                    "${SDL2_TTF_INCLUDE_DIRS}"
                    "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(LoST ${SOURCES})
target_link_libraries(LoST ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

if(WIN32)
    file(GLOB DLL_PATHS "${SDL2_DIR}/${VC_LIB_PATH_SUFFIX}/*.dll")
    foreach(DLL_PATH IN ITEMS ${DLL_PATHS})
        add_custom_command(TARGET LoST POST_BUILD          # Adds a post-build event to target
        COMMAND ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
            ${DLL_PATH}                                    # <--this is in-file
            $<TARGET_FILE_DIR:LoST>)                       # <--this is out-file path
    endforeach(DLL_PATH)
endif()
