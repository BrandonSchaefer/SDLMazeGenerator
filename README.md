Depends:

    https://github.com/BrandonSchaefer/SDLBackend

To compile (Make sure to: export PREFIX=/path/you/want/to/install/to):

    ./build-debug

CMake Options:

    -DCMAKE_BUILD_TYPE=[Debug|Release]
    -DENABLE_TESTS=[ON|OFF]

Controls:

        s       : Solve maze
        g       : Start generating a new maze
        f       : Finish generating current maze
    Arrow Left  : Move to previous maze
    Arrow Right : Move to next maze
    Arrow Up    : Increase generation speed
    Arrow Down  : Decrease generation speed

Maze Algorithms:

    Aldous Broder
    Binary Tree
    Growing Tree
    Hunt and Kill
    Prims
    Recursive Backtracker
    Side Winder
    Wilsons

![Prims example](http://i.imgur.com/9ErClKD.png)
