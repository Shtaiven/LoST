#ifndef GAME_HPP__
#define GAME_HPP__

#include <string>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "sprite.hpp"
#include "timer.hpp"
#include "LoST.hpp"


// Game class creates SDL game window and listens to events
class Game {
    public:
        typedef int (*init_func_t)();
        typedef struct init_t {
            init_func_t setup;
            init_func_t loop;
        } init_t;
        Game(std::string title="Untitled", int width=640, int height=480);
        ~Game();
        void init(init_t config);
        int setup();
        int loop();
        void close();
        void update();
        void capFPS(Uint32 fps);
        void enableVsync(bool enable);


    private:
        // Window and rendering
        SDL_Window* m_window = NULL;
        SDL_Renderer* m_renderer = NULL;
        bool m_quit = false;
        bool m_inited = false;
        int m_width;
        int m_height;

        // Game information and display
        std::string m_title;
        TTF_Font* m_font = NULL;
        std::vector<Sprite*> m_sprite_list;

        // Framerate
        init_t m_config;
        bool m_vsync_enabled = true;
        Uint32 m_fps_cap = 0;
        double m_ms_per_frame = 0;
        Timer m_fps_cap_timer;
        Uint32 m_counted_frames;
        Uint32 m_last_update_ms;
        double m_avg_fps;
        Timer m_fps_timer;
        Sprite* m_fps_sprite = NULL;
        std::stringstream m_fps_string;
        bool m_display_fps = true;
        void loadFPSDisplay(double fps);
};


#endif // GAME_HPP__
