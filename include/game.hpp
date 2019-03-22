#ifndef GAME_HPP__
#define GAME_HPP__

#include "SDL.h"
#include <string>
#include "LoST_Player.hpp"


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
        friend class Sprite;
        SDL_Window* m_window = NULL;
        SDL_Renderer* m_renderer = NULL;
        bool m_quit = false;
        bool m_inited = false;
        int m_width;
        int m_height;
        std::string m_title;
        LoST_Player m_player;
};


#endif // GAME_HPP__
