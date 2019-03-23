#ifndef LOST_PLAYER_HPP__
#define LOST_PLAYER_HPP__

#include "sprite.hpp"


class LoST_Player : public AnimatedSprite {
    public:
        LoST_Player() {
            addFrame(14, 7, 18, 28);
        }

        void handleEvent(const SDL_Event& e) {
            if (noLoad()) return;

            // Handle keyboard events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        moveLeft();
                        break;

                    case SDLK_RIGHT:
                        moveRight();
                        break;

                    case SDLK_UP:
                        jump();
                        break;

                    case SDLK_DOWN:
                        crouch();
                        break;
                }
            }
        }

    private:
        std::map<SDL_EventType, std::function<void(const SDL_Event&)>> m_event_handlers;

        void moveLeft() {
            m_info.x -= 10;
            if (m_info.x < 0) {
                m_info.x = 0;
            }
        }

        void moveRight() {
            int max_w, max_h;
            SDL_GetRendererOutputSize(m_renderer, &max_w, &max_h);

            m_info.x += 10;
            if (m_info.x > max_w - m_info.w) {
                m_info.x = max_w - m_info.w;
            }
        }

        void jump() {

        }

        void crouch() {

        }
};


#endif // LOST_PLAYER_HPP__
