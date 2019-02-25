#include "SDL.h"
#include <string>

#ifndef GAME_HPP__
#define GAME_HPP__

class Game {
    public:
        Game(std::string title, int width=640, int height=480);
        ~Game();
        int setup();
        int loop();

    private:
        SDL_Window* m_window;
        SDL_Surface* m_screen;
        int m_width;
        int m_height;
        bool m_quit;
        bool m_inited;
        std::string m_title;
};

#endif // GAME_HPP__
