#ifndef LOST_ASSETS_HPP__
#define LOST_ASSETS_HPP__

// Define directories
#ifdef _WIN32
    #define LoST_ROOT_DIR "../../"
#else
    #define LoST_ROOT_DIR "../"
#endif // _WIN32
#define LoST_ASSETS_DIR LoST_ROOT_DIR "assets/"

// Define files
#define LoST_ICON_DIR LoST_ASSETS_DIR "icon.png"
#define LoST_ASSETS_PLAYER LoST_ASSETS_DIR "adventurer-spritesheet.png"

#endif // LOST_ASSETS__
