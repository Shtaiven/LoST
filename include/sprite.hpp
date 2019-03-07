#ifndef SPRITE_HPP__
#define SPRITE_HPP__

#include <iostream>
#include <string>
#include "SDL.h"


// Sprite class manages sprites (character, enemies, etc)
class Sprite {
    public:
        Sprite(std::string file="");
        ~Sprite();
        void close();
        bool load();
        void blit(SDL_Surface* dst);

    protected:
        std::string m_file;
        SDL_Surface* m_sprite_surface = NULL;
        SDL_Rect m_rect = {0};
};


// Player class that adds event handling to sprite
class Player : public Sprite {
    public:
        Player(std::string file=""): Sprite(file) {}
        void handleEvent(const SDL_Event& e);
};


#endif // SPRITE_HPP__
