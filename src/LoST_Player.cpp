#include "LoST_Player.hpp"


void LoST_Player::keyEventHandler(const SDL_Event& e) {
    if (noLoad("handleEvent")) return;

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

void LoST_Player::moveLeft() {
    m_info.x -= 10;
    if (m_info.x < 0) {
        m_info.x = 0;
    }
}

void LoST_Player::moveRight() {
    int max_w, max_h;
    SDL_GetRendererOutputSize(m_renderer, &max_w, &max_h);

    m_info.x += 10;
    if (m_info.x > max_w - m_info.w) {
        m_info.x = max_w - m_info.w;
    }
}

void LoST_Player::jump() {

}

void LoST_Player::crouch() {

}
