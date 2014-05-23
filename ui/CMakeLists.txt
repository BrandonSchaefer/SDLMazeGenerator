set (SDL_MAZE_SRC
      Main.cpp
    )

set (SDL_MAZE_HDR
      Main.h
    )

add_subdirectory(sdl_backend)

add_executable(../sdl-maze ${SDL_MAZE_SRC} ${SDL_MAZE_HDR})

include_directories(${SDL_BACKEND_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} ${SDL_MAZE_GENERATORS_SOURCE_DIR}/src)

target_link_libraries (../sdl-maze sdl-backend ${SDL_BACKEND_LIBRARIES})

install (TARGETS ../sdl-maze DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
