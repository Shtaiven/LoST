#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include <string>

#ifndef __GAME_HPP
#define __GAME_HPP

using namespace std;

class Game {
    public:
        Game(string title);
        ~Game();
        int Game::setup();
        int Game::loop();

    private:
        SDL_Window* m_window;
        SDL_Surface* m_screen;
        bool m_quit;
        string m_title;
};

#endif // __GAME_HPP
