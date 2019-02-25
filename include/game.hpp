#ifndef GAME_HPP__
#define GAME_HPP__

#include "SDL.h"
#include <string>


// Game class creates SDL game window and listens to events
class Game {
    public:
        Game(std::string title="Untitled", int width=640, int height=480);
        ~Game();
        int setup();
        int loop();

    private:
        SDL_Window* m_window = NULL;
        SDL_Surface* m_screen = NULL;
        bool m_quit = false;
        bool m_inited = false;
        int m_width;
        int m_height;
        std::string m_title;
};


#endif // GAME_HPP__
