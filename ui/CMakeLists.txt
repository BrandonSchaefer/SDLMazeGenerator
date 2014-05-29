set (SDL_MAZE_SRC
      Cell.cpp
      Main.cpp
      MazeGrid.cpp
      MazeGridController.cpp
      MazeMain.cpp
      TopMenu.cpp
    )

set (SDL_MAZE_HDR
      Cell.h
      Main.h
      MazeGrid.h
      MazeGridController.h
      MazeMain.h
      TopMenu.h
    )

add_subdirectory(sdl_backend)

add_executable(../sdl-maze ${SDL_MAZE_SRC} ${SDL_MAZE_HDR})

include_directories(${SDL_BACKEND_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} ${SDL_MAZE_GENERATORS_SOURCE_DIR}/src ${SDL_MAZE_GENERATORS_SOURCE_DIR})

target_link_libraries (../sdl-maze sdl-backend maze ${SDL_BACKEND_LIBRARIES})

install (TARGETS ../sdl-maze DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
