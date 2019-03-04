# LoST: Legend of Silence Tribute

## Inspiration

LoST is loosely based on a fictional video game described in the short story *Navigators* by Mike Meginnis. The game is described as being similar to Nintendo's *Metroid* for the NES, with a twist: the protagonist becomes weaker as the player progresses through the game.

## Build instructions

* Install cmake version >= 3.7.
* Install SDL2 libraries locally (if on Windows, extract VC libraries to \<project root\>/SDL2).
* In a terminal from the root folder type:

    ```
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

* If compiling for Windows x64, replace `cmake ..` with:

    ```
    cmake -G "Visual Studio 15 2017 Win64" ..
    ```
    or similar, depending on your Visual Studio version. Possible targets are listed in `cmake --help`.

* **NOTE:** If you can't run the compiled executable on Windows, copy SDL2.dll for the appropriate architecture into the executable's directory.
