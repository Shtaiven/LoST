#ifndef LOST_ASSETS_HPP__
#define LOST_ASSETS_HPP__

#include "SDL.h"
#include "sprite.hpp"

// Define directories
#ifdef _WIN32
    #define LoST_ROOT_DIR "../../"
#else
    #define LoST_ROOT_DIR "../"
#endif // _WIN32
#define LoST_ASSETS_DIR LoST_ROOT_DIR "assets/"

// Define icon
#define LoST_ASSETS_ICON LoST_ASSETS_DIR "icon.png"

// Define fonts
#define LoST_ASSETS_FONT_TITLE LoST_ASSETS_DIR "De-Valencia.ttf"
#define LoST_ASSETS_FONT_TITLE_POINT 128
#define LoST_ASSETS_FONT_GAME LoST_ASSETS_FONT_TITLE
#define LoST_ASSETS_FONT_GAME_POINT 24

// Define a macro for easy animation setting within an AnimatedSprite
#define LoST_SET_ANIMATION(_sprite_name, _animation) do { \
    setStartFrameIndex(LoST_ASSETS_ ## _sprite_name ## _ ## _animation ## _START_INDEX); \
    setEndFrameIndex(LoST_ASSETS_ ## _sprite_name ## _ ## _animation ## _END_INDEX); \
    setCurrentFrameIndex(LoST_ASSETS_ ## _sprite_name ## _ ## _animation ## _START_INDEX); \
    loop(LoST_ASSETS_ ## _sprite_name ## _ ## _animation ## _LOOPS); \
} while(0)

// Define a macro that returns true if we are within the animation given
#define LoST_IS_WITHIN_ANIMATION(_sprite_name, _animation) \
((bool)(getCurrentFrameIndex() >= LoST_ASSETS_ ## _sprite_name ## _ ## _animation ## _START_INDEX && \
        getCurrentFrameIndex() <= LoST_ASSETS_ ## _sprite_name ## _ ## _animation ## _END_INDEX) \
)

// Define player
#define LoST_ASSETS_PLAYER LoST_ASSETS_DIR "adventurer-spritesheet.png"
#define LoST_ASSETS_PLAYER_FRAME_WIDTH 50
#define LoST_ASSETS_PLAYER_FRAME_HEIGHT 36
#define LoST_ASSETS_PLAYER_IDLE_LOOPS (true)
#define LoST_ASSETS_PLAYER_IDLE_NUM_FRAMES (4)
#define LoST_ASSETS_PLAYER_IDLE_START_INDEX (0)
#define LoST_ASSETS_PLAYER_IDLE_END_INDEX (LoST_ASSETS_PLAYER_IDLE_START_INDEX+LoST_ASSETS_PLAYER_IDLE_NUM_FRAMES-1)
#define LoST_ASSETS_PLAYER_IDLE_FRAME0 0, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_IDLE_FRAME1 1*LoST_ASSETS_PLAYER_FRAME_WIDTH, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_IDLE_FRAME2 2*LoST_ASSETS_PLAYER_FRAME_WIDTH, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_IDLE_FRAME3 3*LoST_ASSETS_PLAYER_FRAME_WIDTH, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_RUN_LOOPS (true)
#define LoST_ASSETS_PLAYER_RUN_NUM_FRAMES (6)
#define LoST_ASSETS_PLAYER_RUN_START_INDEX (LoST_ASSETS_PLAYER_IDLE_END_INDEX+1)
#define LoST_ASSETS_PLAYER_RUN_END_INDEX (LoST_ASSETS_PLAYER_RUN_START_INDEX+LoST_ASSETS_PLAYER_RUN_NUM_FRAMES-1)
#define LoST_ASSETS_PLAYER_RUN_FRAME0 1*LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_RUN_FRAME1 2*LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_RUN_FRAME2 3*LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_RUN_FRAME3 4*LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_RUN_FRAME4 5*LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_RUN_FRAME5 6*LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_CROUCH_LOOPS (true)
#define LoST_ASSETS_PLAYER_CROUCH_NUM_FRAMES (4)
#define LoST_ASSETS_PLAYER_CROUCH_START_INDEX (LoST_ASSETS_PLAYER_RUN_END_INDEX+1)
#define LoST_ASSETS_PLAYER_CROUCH_END_INDEX (LoST_ASSETS_PLAYER_CROUCH_START_INDEX+LoST_ASSETS_PLAYER_CROUCH_NUM_FRAMES-1)
#define LoST_ASSETS_PLAYER_CROUCH_FRAME0 4*LoST_ASSETS_PLAYER_FRAME_WIDTH, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_CROUCH_FRAME1 5*LoST_ASSETS_PLAYER_FRAME_WIDTH, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_CROUCH_FRAME2 6*LoST_ASSETS_PLAYER_FRAME_WIDTH, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_CROUCH_FRAME3 0, LoST_ASSETS_PLAYER_FRAME_HEIGHT+1, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_LOOPS (false)
#define LoST_ASSETS_PLAYER_JUMP_NUM_FRAMES (8)
#define LoST_ASSETS_PLAYER_JUMP_START_INDEX (LoST_ASSETS_PLAYER_CROUCH_END_INDEX+1)
#define LoST_ASSETS_PLAYER_JUMP_END_INDEX (LoST_ASSETS_PLAYER_JUMP_START_INDEX+LoST_ASSETS_PLAYER_JUMP_NUM_FRAMES-1)
#define LoST_ASSETS_PLAYER_JUMP_FRAME0 2*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*2, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME1 3*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*2, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME2 4*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*2, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME3 5*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*2, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME4 6*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*2, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME5 0, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*3, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME6 1*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*3, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT
#define LoST_ASSETS_PLAYER_JUMP_FRAME7 2*LoST_ASSETS_PLAYER_FRAME_WIDTH, (LoST_ASSETS_PLAYER_FRAME_HEIGHT+1)*3, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT


#endif // LOST_ASSETS__
