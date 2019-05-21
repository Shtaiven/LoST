#ifndef LOST_PLAYER_HPP__
#define LOST_PLAYER_HPP__

#include "sprite.hpp"


class LoST_Player : public AnimatedSprite {
    public:
    LoST_Player() {
        ASSIGN_SDL_RECT(m_render_rect, 0, 0, LoST_ASSETS_PLAYER_FRAME_WIDTH, LoST_ASSETS_PLAYER_FRAME_HEIGHT);
        ASSIGN_SDL_RECT(m_collision_rect, 16, 7, 17, 29);
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
        setSpeed(1.0/7.5);
        LoST_SET_ANIMATION(PLAYER, IDLE);
    }

    void handleState(Uint32 ms=0) {
        if (!isLoaded()) return;
        const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
        SDL_Point prev_pos = { m_render_rect.x, m_render_rect.y };
        bool is_jumping = LoST_IS_WITHIN_ANIMATION(PLAYER, JUMP) && (getCurrentFrameIndex() != LoST_ASSETS_PLAYER_JUMP_END_INDEX);
        bool is_running = LoST_IS_WITHIN_ANIMATION(PLAYER, RUN);
        bool is_crouching = LoST_IS_WITHIN_ANIMATION(PLAYER, CROUCH);
        bool is_idle = LoST_IS_WITHIN_ANIMATION(PLAYER, IDLE);

        // Handle keyboard state
        if (!(current_key_states[SDL_SCANCODE_LEFT]  ||
              current_key_states[SDL_SCANCODE_RIGHT] ||
              current_key_states[SDL_SCANCODE_UP]    ||
              current_key_states[SDL_SCANCODE_DOWN]) &&
              !is_jumping
            ) {
            if (!is_idle) {
                LoST_SET_ANIMATION(PLAYER, IDLE);
            }
        } else if (current_key_states[SDL_SCANCODE_DOWN] && !is_jumping) {
            if (!is_crouching) {
                LoST_SET_ANIMATION(PLAYER, CROUCH);
            }
        } else {
            if (current_key_states[SDL_SCANCODE_LEFT]) {
                moveLeft();
            }
            if (current_key_states[SDL_SCANCODE_RIGHT]) {
                moveRight();
            }
            if (current_key_states[SDL_SCANCODE_UP] && !is_jumping) {
                LoST_SET_ANIMATION(PLAYER, JUMP);
            }
        }

        // Checking if we should update sprite animation
        // Are we currently jumping? If so, stay in jump animation
        if (!is_jumping) {
            // Has our x position changed?
            if (m_render_rect.x > prev_pos.x && getFlip() != SDL_FLIP_NONE) {
                setFlip(SDL_FLIP_NONE);
            } else if (m_render_rect.x < prev_pos.x && getFlip() != SDL_FLIP_HORIZONTAL) {
                setFlip(SDL_FLIP_HORIZONTAL);
            }

            // Are we already in the running animation
            if (!is_running && prev_pos.x != m_render_rect.x) {
                LoST_SET_ANIMATION(PLAYER, RUN);
            }
        }
    }

    private:
    int m_speed = 10;

    void moveLeft() {
        m_render_rect.x -= m_speed;
        if (m_render_rect.x < 0) {
            m_render_rect.x = 0;
        }
    }

    void moveRight() {
        int max_w, max_h;
        SDL_GetRendererOutputSize(m_renderer, &max_w, &max_h);

        m_render_rect.x += m_speed;
        if (m_render_rect.x > max_w - m_render_rect.w) {
            m_render_rect.x = max_w - m_render_rect.w;
        }
    }
};


#endif // LOST_PLAYER_HPP__
