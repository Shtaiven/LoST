#ifndef LOST_PLAYER_HPP__
#define LOST_PLAYER_HPP__

#include "sprite.hpp"


class LoST_Player : public AnimatedSprite {
    public:
    LoST_Player() {
        ASSIGN_SDL_RECT(m_render_rect, 0, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT);
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
        setSpeed(1.0/30);
        idle();
    }

    void handleEvent(const SDL_Event& e) {
        if (!isLoaded()) return;

        // Handle keyboard events
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    moveLeft(m_prev_keydown != SDLK_LEFT);
                    break;

                case SDLK_RIGHT:
                    moveRight(m_prev_keydown != SDLK_RIGHT);
                    break;

                case SDLK_UP:
                    jump(m_prev_keydown != SDLK_UP);
                    break;

                case SDLK_DOWN:
                    crouch(m_prev_keydown != SDLK_DOWN);
                    break;
            }
            m_prev_keydown = e.key.keysym.sym;
        } else if (e.type == SDL_KEYUP) {
            idle();
            m_prev_keydown = SDLK_UNKNOWN;
        }
    }

    private:
    int m_speed = 30;
    int m_prev_keydown = SDLK_UNKNOWN;

    void moveLeft(bool update_anim=false) {
        if (update_anim)  {
            LoST_SET_ANIMATION(RUN);
            setFlip(SDL_FLIP_HORIZONTAL);
        }

        m_render_rect.x -= m_speed;
        if (m_render_rect.x < 0) {
            m_render_rect.x = 0;
        }
    }

    void moveRight(bool update_anim=false) {
        if (update_anim)  {
            LoST_SET_ANIMATION(RUN);
            setFlip(SDL_FLIP_NONE);
        }

        int max_w, max_h;
        SDL_GetRendererOutputSize(m_renderer, &max_w, &max_h);

        m_render_rect.x += m_speed;
        if (m_render_rect.x > max_w - m_render_rect.w) {
            m_render_rect.x = max_w - m_render_rect.w;
        }
    }

    void jump(bool update_anim=false) {
        if (update_anim) {
            LoST_SET_ANIMATION(JUMP);
        }
    }

    void crouch(bool update_anim=false) {
        if (update_anim) {
            LoST_SET_ANIMATION(CROUCH);
        }
    }

    void idle() {
        setStartFrameIndex(LoST_ASSETS_PLAYER_IDLE_START_INDEX);
        setEndFrameIndex(LoST_ASSETS_PLAYER_IDLE_END_INDEX);
        loop(LoST_ASSETS_PLAYER_IDLE_LOOPS);
    }
};


#endif // LOST_PLAYER_HPP__
