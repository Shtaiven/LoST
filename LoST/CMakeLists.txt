include_directories("${CMAKE_CURRENT_LIST_DIR}"
                    "${CMAKE_CURRENT_LIST_DIR}/include"
                    "${CMAKE_CURRENT_LIST_DIR}/src")
file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_SOURCES *.cpp *.c)

add_executable(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} LGE)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# Move DLLs required by Windows binary into build directory so game runs properly
if(WIN32 AND SDL2_DIR AND COPY_DLLS)
    # Check is compiling for x86 or x64
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SDL_LIB_PATH "${SDL2_DIR}/lib/x64")
    else()
    set(SDL_LIB_PATH "${SDL2_DIR}/lib/x86")
    endif()

    # Copy DLLs into build directory
    file(GLOB DLL_PATHS "${SDL_LIB_PATH}/*.dll")
    foreach(DLL_PATH IN ITEMS ${DLL_PATHS})
        add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD  # Adds a post-build event to target
            COMMAND ${CMAKE_COMMAND} -E copy_if_different           # which executes "cmake -E copy_if_different..."
            ${DLL_PATH}                                             # <--this is in-file
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)               # <--this is out-file path
    endforeach(DLL_PATH)
endif()
