find_package (PkgConfig)

set (SDL_BACKEND_REQUIRED
     sdl2
     SDL2_image
     SDL2_mixer
     SDL2_ttf
     sigc++-2.0
    )

pkg_check_modules(SDL_BACKEND REQUIRED ${SDL_BACKEND_REQUIRED})

set (SDL_BACKEND_SRC
     Color.cpp
     Entity.cpp
     EntityCreator.cpp
     EntityHashTable.cpp
     EntityLayer.cpp
     ImageTexture.cpp
     MainLoop.cpp
     GraphicsRenderer.cpp
     Point.cpp
     Rect.cpp
     RenderableGeometry.cpp
     SDLTimer.cpp
     Size.cpp
     StringTexture.cpp
     StringTextureCreator.cpp
     Timer.cpp
     World.cpp
    )

set (SDL_BACKEND_HDR
     Color.h
     Entity.h
     EntityCreator.h
     EntityHashTable.h
     EntityLayer.h
     ImageTexture.h
     MainLoop.h
     GraphicsRenderer.h
     Rect.h
     RenderableGeometry.h
     Renderable.h
     SDLTimer.h
     Size.h
     StringTexture.h
     StringTextureCreator.h
     StringTextureData.h
     Timer.h
     World.h
    )

set (PREFIXDIR "${CMAKE_INSTALL_PREFIX}")
set (EXEC_PREFIX "${CMAKE_INSTALL_PREFIX}")
set (LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
set (INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")

configure_file (sdl-backend.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/sdl-backend.pc @ONLY)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/sdl-backend.pc
         DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)

include_directories (${SDL_BACKEND_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_library (sdl-backend SHARED ${SDL_BACKEND_SRC} ${SDL_BACKEND_HDR})

install (TARGETS sdl-backend
         RUNTIME DESTINATION bin
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
        )
