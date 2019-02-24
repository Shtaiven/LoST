#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include <string>

#ifndef GAME_HPP__
#define GAME_HPP__

using namespace std;

class Game {
    public:
        Game(string title);
        ~Game();
        int setup();
        int loop();

    private:
        SDL_Window* m_window;
        SDL_Surface* m_screen;
        bool m_quit;
        string m_title;
};

#endif // GAME_HPP__
