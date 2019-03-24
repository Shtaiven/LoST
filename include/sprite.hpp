#ifndef SPRITE_HPP__
#define SPRITE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "SDL.h"


#define ASSIGN_SDL_RECT(_rect, _x, _y, _w, _h) do { \
    (_rect).x=_x; (_rect).y=_y; (_rect).w=_w; (_rect.h)=_h; \
} while(0)


// Sprite class manages sprites (character, enemies, etc)
class Sprite {
    public:
        ~Sprite();
        void free();
        bool load(std::string file, SDL_Renderer* renderer, const SDL_Rect* info=NULL);
        void getInfo(SDL_Rect* buf);
        void setInfo(const SDL_Rect* info);
        void setPosition(int x, int y);
        void setPosition(const SDL_Rect* pos);
        void setSize(int w, int h);
        void setSize(const SDL_Rect* size);
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha);
        void setBlendMode(SDL_BlendMode blending);
        virtual int render(const SDL_Rect* clip=NULL);
        virtual int render(int x, int y, const SDL_Rect* clip=NULL);
        virtual void handleEvent(const SDL_Event& e) {}

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
        void addFrame(int x, int y, int w, int h);
        void addFrame(const SDL_Rect& frame);
        void addFrames(const std::vector<SDL_Rect>& frames);
        void delFrames();
        void delFrames(size_t n);
        size_t numFrames();
        void getFrame(size_t index, SDL_Rect* buf);
        void loop(bool loop);
        float getSpeed();
        void setSpeed(float speed=1.0);
        int getFrameDelay();
        void setFrameDelay(int delay=0);

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
        size_t m_animation_len = 0;
        bool m_loop = false;
        int m_frame_delay = 0;
        int m_frames_skipped = 0;
        void updateAnimationLen();
        size_t nextFrameIndex();

};


#endif // SPRITE_HPP__
