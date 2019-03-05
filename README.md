# LoST: Legend of Silence Tribute

## Inspiration

LoST is loosely based on a fictional video game described in the short story *Navigators* by Mike Meginnis. The game is described as being similar to Nintendo's *Metroid* for the NES, with a twist: the protagonist becomes weaker as the player progresses through the game.

## Build instructions

* Install cmake version >= 3.7.
* Install SDL2 development libraries (if on Windows, extract VC development libraries to \<project root\>/SDL2).

### macOS and Linux
* In a terminal from the root folder, type:

    ```
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

### Windows
* Install Visual Studio (any version supported by cmake, see `cmake --help`)
* In a cmd or MSYS/MinGW, type:

    ```
    mkdir build
    cd build
    cmake -G <platform> ..
    cmake --build . --config <cfg>
    ```

    where `<platform>` is one of the Visual Studio versions listed when typing `cmake --help`

    e.g.

    ```
    cmake -G "Visual Studio 15 2017 Win64" ..
    ```

    and where `<cfg>` is one of:

    * `Release`
    * `RelWithDebInfo`
    * `MinSizeRel`
    * `Debug`

    e.g.

    ```
    cmake --build . --config Release
    ```

    to build for those targets.

* **NOTE:** If you can't run the compiled executable on Windows, copy SDL2.dll for the appropriate architecture into the executable's directory.
