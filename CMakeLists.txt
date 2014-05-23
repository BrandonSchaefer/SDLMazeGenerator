project (SDL_MAZE_GENERATORS)
cmake_minimum_required (VERSION 2.8.9)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++0x -Werror -Wall -pedantic -Wcast-align -Wempty-body -Wformat-security -Winit-self -Warray-bounds")

set (CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set (CMAKE_CXX_FLAGS_RELEASE "-O2")

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (RESDIR "${CMAKE_INSTALL_PREFIX}/share/bouncy-ball/resources")
configure_file (${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h) 

file (GLOB _datafiles "${CMAKE_CURRENT_SOURCE_DIR}/resources/*")
install (FILES ${_datafiles} DESTINATION ${RESDIR})

add_subdirectory(maze)
add_subdirectory(tests)
add_subdirectory(ui)
