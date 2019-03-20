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
        void free();
        bool load(std::string file, SDL_Renderer* renderer, const SDL_Rect* info=NULL);
        int render();
        int render(int x, int y);
        void getInfo(SDL_Rect* buf);
        void setInfo(const SDL_Rect* info);
        void setPosition(int x, int y);
        void setPosition(const SDL_Rect* pos);
        void setSize(int w, int h);
        void setSize(const SDL_Rect* size);
        virtual void handleEvent(const SDL_Event& e) {}

    protected:
        std::string m_file = "";
        SDL_Texture* m_texture = NULL;
        SDL_Renderer* m_renderer = NULL;
        SDL_Rect m_info = {0};
        bool noLoad(std::string func_name="");
};


// Player class that adds event handling to sprite
class Player : public Sprite {
    public:
        void handleEvent(const SDL_Event& e);
};


#endif // SPRITE_HPP__
