#include "sprite.hpp"


Sprite::Sprite(std::string file) {
    m_file = file;
}


Sprite::~Sprite() {
    close();
}


void Sprite::close() {
    // Deallocate the surface
    SDL_FreeSurface(m_sprite_surface);
    m_sprite_surface = NULL;
}


bool Sprite::load(int x, int y) {
    // Load the sprite image
    m_sprite_surface = SDL_LoadBMP(m_file.c_str());
    if (!m_sprite_surface) {
        std::cerr << "Unable to load image "
                  << m_file
                  << "! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
        return false;
    }
    m_rect.w = m_sprite_surface->w;
    m_rect.h = m_sprite_surface->h;
    m_rect.x = x;
    m_rect.y = y;

    return true;
}


// Blit the sprite to the dst surface
void Sprite::blit(SDL_Surface* dst) {
    //Apply the image
    SDL_BlitSurface(m_sprite_surface, NULL, dst, &m_rect);
}


int Sprite::x() {
    return m_rect.x;
}


int Sprite::y() {
    return m_rect.y;
}


int Sprite::w() {
    return m_rect.w;
}


int Sprite::h() {
    return m_rect.h;
}


void Sprite::set_position(int x, int y) {
    m_rect.x = x;
    m_rect.y = y;
}


// Handle incoming events
void Player::handleEvent(const SDL_Event& e, const SDL_Surface *screen_surface)
{
    // TODO: Handle keyboard events
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_LEFT) {
            m_rect.x -= 10;
            if (m_rect.x < 0) {
                m_rect.x = 0;
            }
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
            m_rect.x += 10;
            if (m_rect.x > screen_surface->w - m_sprite_surface->w) {
                m_rect.x = screen_surface->w - m_sprite_surface->w;
            }

        }
    }
}
