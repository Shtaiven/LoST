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
        Game(std::string title="Untitled", int width=640, int height=480);
        ~Game();
        int setup();
        int loop();
        void close();
        void update();

    private:
        SDL_Window* m_window = NULL;
        SDL_Renderer* m_renderer = NULL;
        bool m_quit = false;
        bool m_inited = false;
        int m_width;
        int m_height;
        std::string m_title;
        TTF_Font* m_font = NULL;
        std::vector<Sprite*> m_sprite_list;
        Uint32 m_counted_frames;
        Timer m_fps_timer;
        Sprite* m_fps_sprite = NULL;
        std::stringstream m_fps_string;
        void loadFPSDisplay(float fps);
};


#endif // GAME_HPP__
