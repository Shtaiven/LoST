#ifndef LOST_PLAYER_HPP__
#define LOST_PLAYER_HPP__

#include "sprite.hpp"

class LoST_Player : public AnimatedSprite, public EventSprite {
    private:
        void keyEventHandler();
        void moveLeft();
        void moveRight();
        void jump();
        void duck();
};

#endif // LOST_PLAYER_HPP__
