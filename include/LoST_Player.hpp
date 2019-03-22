#ifndef LOST_PLAYER_HPP__
#define LOST_PLAYER_HPP__

#include "sprite.hpp"

class LoST_Player : public AnimatedSprite, public EventSprite {
    private:
        void moveLeft();
        void moveRight();
        void jump();
        void crouch();

    public:
    // FIXME: This doesn't compile. Investigate
        void keyEventHandler(const SDL_Event& e);
        LoST_Player() {
            SDL_Rect player_clip = {
                14, // x
                7,  // y
                18, // w
                28  // h
            };
            addFrames(player_clip);
            addEventHandler(SDL_KEYDOWN, keyEventHandler);
        }
};

#endif // LOST_PLAYER_HPP__
