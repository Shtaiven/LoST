#ifndef GAME_HPP__
#define GAME_HPP__

#include <string>
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
};


#endif // GAME_HPP__
