#ifndef SPRITE_HPP__
#define SPRITE_HPP__

#include <iostream>
#include <string>
#include "SDL.h"


// Sprite class manages sprites (character, enemies, etc)
class Sprite {
    public:
        Sprite();
        ~Sprite();
        void close();
        bool load(std::string file, const SDL_Rect* info=NULL);
        void render(const SDL_Renderer* renderer);
        void get_info(SDL_Rect* buf);
        void set_info(const SDL_Rect* info);
        void set_position(int x, int y);
        void set_position(const SDL_Rect* pos);
        void set_size(int w, int h);
        void set_size(const SDL_Rect* size);

    protected:
        std::string m_file = "";
        SDL_Texture* m_sprite_texture = NULL;
        SDL_Rect m_info = {0};
        bool noLoad(std::string func_name="");
};


// Player class that adds event handling to sprite
class Player : public Sprite {
    public:
        Player(): Sprite() {}
        void handleEvent(const SDL_Event& e);
};


#endif // SPRITE_HPP__
