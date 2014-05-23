prefix=@PREFIXDIR@
exec_prefix=@EXEC_PREFIX@
libdir=@LIBDIR@
includedir=@INCLUDEDIR@

Name: SDL Backend
Library
Description: Simple SDL2 engine
Version: @VERSION@
Libs: -L${libdir} -lsdl-backend
Cflags: -I${includedir}
Requires: sdl2 SDL2_image SDL2_mixer SDL2_ttf sigc++-2.0
