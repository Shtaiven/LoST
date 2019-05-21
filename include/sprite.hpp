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
        virtual ~Sprite();
        void free();
        bool loadImage(std::string file, SDL_Renderer* renderer, const SDL_Rect* render_rect=NULL);
        bool loadText(TTF_Font* font, SDL_Renderer* renderer, std::string text, const SDL_Color& color={0,0,0,0xFF}, const SDL_Point& pos={0,0});
        void getRenderRect(SDL_Rect* render_rect);
        void setRenderRect(const SDL_Rect* render_rect);
        void getCollisionRect(SDL_Rect* collision_rect);
        void setCollisionRect(const SDL_Rect* collision_rect);
        bool hasCollision();
        void setCenter(SDL_Point* center);
        int getX();
        void setX(int x);
        int getY();
        void setY(int y);
        void setPosition(int x, int y);
        int getWidth();
        void setWidth(int w);
        int getHeight();
        void setHeight(int h);
        void setSize(int w, int h);
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha);
        void setBlendMode(SDL_BlendMode blending);
        Uint8 getFlip();
        void setFlip(Uint8 flip);
        double getRotation();
        void setRotation(double angle);
        bool isLoaded();
        void clip(SDL_Rect* clip);
        virtual int render();
        virtual int render(int x, int y);
        virtual void handleEvent(const SDL_Event& e) {}
        virtual void handleState(Uint32 ms=0) {}
        static bool checkCollision(Sprite* a, Sprite* b);

    protected:
        void loadTextureFromSurface(SDL_Surface* surface, SDL_Renderer* renderer, const SDL_Rect* render_rect);
        std::string m_file;
        SDL_Texture* m_texture = NULL;
        SDL_Renderer* m_renderer = NULL;
        SDL_Rect m_render_rect = {0};
        SDL_Rect m_collision_rect = {0};
        SDL_Rect* m_clip = NULL;
        SDL_Point* m_center = NULL;
        Uint8 m_flip = SDL_FLIP_NONE;
        double m_rotation = 0.0;
        bool m_collision_debug = true;
};


// AnimatedSprite class allows adding animations through the use of a spritesheet
class AnimatedSprite : virtual public Sprite {
    public:
        virtual ~AnimatedSprite();

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
        double getSpeed();
        void setSpeed(double speed=1.0);
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
