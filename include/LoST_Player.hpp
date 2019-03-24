#ifndef LOST_PLAYER_HPP__
#define LOST_PLAYER_HPP__

#include "sprite.hpp"


class LoST_Player : public AnimatedSprite {
    public:
        LoST_Player() {
            ASSIGN_SDL_RECT(m_info, 0, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT);
            addFrame(LoST_ASSETS_PLAYER_IDLE_FRAME0);
            addFrame(LoST_ASSETS_PLAYER_IDLE_FRAME1);
            addFrame(LoST_ASSETS_PLAYER_IDLE_FRAME2);
            addFrame(LoST_ASSETS_PLAYER_IDLE_FRAME3);
            addFrame(LoST_ASSETS_PLAYER_RUN_FRAME0);
            addFrame(LoST_ASSETS_PLAYER_RUN_FRAME1);
            addFrame(LoST_ASSETS_PLAYER_RUN_FRAME2);
            addFrame(LoST_ASSETS_PLAYER_RUN_FRAME3);
            addFrame(LoST_ASSETS_PLAYER_RUN_FRAME4);
            addFrame(LoST_ASSETS_PLAYER_RUN_FRAME5);
            addFrame(LoST_ASSETS_PLAYER_CROUCH_FRAME0);
            addFrame(LoST_ASSETS_PLAYER_CROUCH_FRAME1);
            addFrame(LoST_ASSETS_PLAYER_CROUCH_FRAME2);
            addFrame(LoST_ASSETS_PLAYER_CROUCH_FRAME3);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME0);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME1);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME2);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME3);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME4);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME5);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME6);
            addFrame(LoST_ASSETS_PLAYER_JUMP_FRAME7);
            setStartFrameIndex(LoST_ASSETS_PLAYER_IDLE_START_INDEX);
            setEndFrameIndex(LoST_ASSETS_PLAYER_IDLE_END_INDEX);
            loop(LoST_ASSETS_PLAYER_IDLE_LOOPS);
            setFrameDelay(60);
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
