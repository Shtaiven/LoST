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


bool Sprite::load() {
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

    return true;
}


// Blit the sprite to the dst surface
void Sprite::blit(SDL_Surface* dst) {
    //Apply the image
    SDL_BlitSurface(m_sprite_surface, NULL, dst, &m_rect);
}


// Handle incoming events
void Player::handleEvent(const SDL_Event& e)
{
    // TODO: Handle keyboard events
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
                m_rect.y -= 2;
                break;

            case SDLK_DOWN:
                m_rect.y += 2;
                break;

            case SDLK_LEFT:
                m_rect.x -= 2;
                break;

            case SDLK_RIGHT:
                m_rect.x += 2;
                break;

            default:
                break;
        }
    }
}
