#ifndef SPRITE_HPP__
#define SPRITE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "SDL.h"


// Sprite class manages sprites (character, enemies, etc)
class Sprite {
    public:
        ~Sprite();
        void free();
        bool load(std::string file, SDL_Renderer* renderer, const SDL_Rect* info=NULL);
        int render(const SDL_Rect* clip=NULL);
        int render(int x, int y, const SDL_Rect* clip=NULL);
        void getInfo(SDL_Rect* buf);
        void setInfo(const SDL_Rect* info);
        void setPosition(int x, int y);
        void setPosition(const SDL_Rect* pos);
        void setSize(int w, int h);
        void setSize(const SDL_Rect* size);

    protected:
        std::string m_file = "";
        SDL_Texture* m_texture = NULL;
        SDL_Renderer* m_renderer = NULL;
        SDL_Rect m_info = {0};
        bool noLoad(std::string func_name="");
};


// AnimatedSprite class allows adding animations through the use of a spritesheet
class AnimatedSprite : virtual public Sprite {
    public:
        // Redefined from Sprite
        int render();
        int render(int x, int y);

        // Frame manipulation
        void addFrames(const SDL_Rect& frame);
        void addFrames(const std::vector<SDL_Rect>& frames);
        void delFrames();
        void delFrames(size_t n);
        size_t numFrames();
        void getFrame(size_t index, SDL_Rect* buf);

        // Index manipulation
        size_t getCurrentFrameIndex();
        void setCurrentFrameIndex(size_t index);
        size_t getStartFrameIndex();
        void setStartFrameIndex(size_t index);
        size_t getEndFrameIndex();
        void setEndFrameIndex(size_t index);

    private:
        std::vector<SDL_Rect> m_frames;
        size_t m_current_frame_index = 0;
        size_t m_start_frame_index = 0;
        size_t m_end_frame_index = 0;
};


// EventSprite class that adds event handling to Sprite
class EventSprite : virtual public Sprite {
    public:
        void addEventHandler(SDL_EventType event_type, void (*handler)(const SDL_Event&));
        void handleEvent(const SDL_Event& e);

    private:
        std::map<SDL_EventType, std::function<void(const SDL_Event&)>> m_event_handlers;
};


#endif // SPRITE_HPP__
