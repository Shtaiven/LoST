# LoST: Legend of Silence Tribute

## Inspiration

LoST is loosely based on a fictional video game described in the short story *Navigators* by Mike Meginnis. The game is described as being similar to Nintendo's *Metroid* for the NES, with a twist: the protagonist becomes weaker as the player progresses through the game.

## Build instructions

* Install cmake version >= 3.7.

### macOS and Linux

* Install [SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), and [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) development libraries for your platform.
* In a terminal window from the root folder, type:

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

### Windows

* Install Visual Studio (any version supported by cmake, see `cmake --help`)
* In a PowerShell window, type:

    ```PowerShell
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser -Force
    .\install-libs.ps1
    ```

    then wait for the script to complete.

* In a PowerShell, cmd, or MinGW/MSYS window, type:

    ```PowerShell
    mkdir build
    cd build
    cmake -G <platform> ..
    cmake --build .
    ```

    where `<platform>` is one of the Visual Studio versions listed when typing `cmake --help`

    e.g.

    ```PowerShell
    cmake -G "Visual Studio 15 2017 Win64" ..
    ```

    Optionally, you can build using:

    ```PowerShell
    cmake --build . --config <cfg>
    ```

    where `<cfg>` is one of:

    * `Release`
    * `RelWithDebInfo`
    * `MinSizeRel`
    * `Debug`

    e.g.

    ```PowerShell
    cmake --build . --config Release
    ```

    to build for those targets.

* **NOTE:** If you can't run the compiled executable on Windows, copy SDL2.dll for the appropriate architecture into the executable's directory and run the compiled executable directly from there.
