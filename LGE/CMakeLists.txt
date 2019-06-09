set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}"
                    "${CMAKE_CURRENT_LIST_DIR}/include"
                    "${CMAKE_CURRENT_LIST_DIR}/src"
                    "${SDL2_INCLUDE_DIRS}"
                    "${SDL2_IMAGE_INCLUDE_DIRS}"
                    "${SDL2_TTF_INCLUDE_DIRS}")

file(GLOB_RECURSE LGE_SOURCES *.cpp *.c)
add_library(LGE_LIB ${LGE_SOURCES})
target_link_libraries(LGE_LIB ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_include_directories(LGE_LIB PUBLIC
                           "${CMAKE_CURRENT_LIST_DIR}/include"
                           "${SDL2_INCLUDE_DIRS}"
                           "${SDL2_IMAGE_INCLUDE_DIRS}"
                           "${SDL2_TTF_INCLUDE_DIRS}")
