include_directories("${CMAKE_CURRENT_LIST_DIR}"
                    "${CMAKE_CURRENT_LIST_DIR}/include"
                    "${CMAKE_CURRENT_LIST_DIR}/src")
file(GLOB_RECURSE LoST_SOURCES *.cpp *.c)

add_executable(${CMAKE_PROJECT_NAME} ${LoST_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} LGE_LIB)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
