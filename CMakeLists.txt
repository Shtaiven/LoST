cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)
project(LoST)

# Must be set to find SDL2 on Windows
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2")

add_subdirectory(LGE)
add_subdirectory(LoST)

if(WIN32)
    file(GLOB DLL_PATHS "${SDL2_DIR}/${VC_LIB_PATH_SUFFIX}/*.dll")
    foreach(DLL_PATH IN ITEMS ${DLL_PATHS})
        add_custom_command(TARGET LoST_EXE POST_BUILD      # Adds a post-build event to target
        COMMAND ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
            ${DLL_PATH}                                    # <--this is in-file
            $<TARGET_FILE_DIR:LoST_EXE>)                   # <--this is out-file path
    endforeach(DLL_PATH)
endif()
