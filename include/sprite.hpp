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

    private:
        std::string m_file;
        SDL_Surface* m_sprite_surface = NULL;
};


#endif // SPRITE_HPP__
