#include "SDL_image.h"
#include "sprite.hpp"


Sprite::Sprite() {}


Sprite::~Sprite() {
    close();
}


void Sprite::close() {
    // Deallocate the texture
    SDL_DestroyTexture(m_sprite_texture);
    m_sprite_texture = NULL;
}


bool Sprite::load(std::string file, const SDL_Rect* info) {
    bool result = true;

    // Load the sprite image
    SDL_Surface *temp_surface = IMG_Load(file.c_str());
    if (!temp_surface) {
        std::cerr << "Unable to load image "
                  << file
                  << "! SDL_image Error: "
                  << IMG_GetError()
                  << std::endl;
        result = false;
    }

    // Optimize image performance
    m_sprite_surface = SDL_ConvertSurface(temp_surface, screen_surface->format, NULL);
    if (!m_sprite_surface) {
        std::cerr << "Unable to optimize image "
                  << file
                  << "! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
        result = false;
    }

    // Free memory of temp_surface and store new surface
    SDL_FreeSurface(temp_surface);

    set_info(info);

    return result;
}


// Blit the sprite to the dst surface
void Sprite::render(const SDL_Renderer* renderer) {
    if (noLoad("blit")) return;

    //Apply the image
    if (m_stretch_rect) {
        m_stretch_rect->x = m_info.x;
        m_stretch_rect->y = m_info.y;
        SDL_BlitScaled(m_sprite_surface, NULL, m_screen_surface, m_stretch_rect);
    } else {
        SDL_BlitSurface(m_sprite_surface, NULL, m_screen_surface, &m_info);
    }
}


void Sprite::get_info(SDL_Rect* buf) {
    if (buf) {
        memcpy(buf, &m_info, sizeof(SDL_Rect));
    }
}


void Sprite::set_info(const SDL_Rect* info) {
    if (info) {
        memcpy(&m_info, info, sizeof(SDL_Rect));
    }
}


void Sprite::set_position(int x, int y) {
    m_info.x = x;
    m_info.y = y;
}


void Sprite::set_position(const SDL_Rect* pos) {
    m_info.x = pos->x;
    m_info.y = pos->y;
}


void Sprite::set_size(int w, int h) {
    m_info.w = w;
    m_info.h = h;
}


void Sprite::set_size(const SDL_Rect* size) {
    m_info.w = size->w;
    m_info.h = size->h;
}


bool Sprite::noLoad(std::string func_name) {
    if (!m_sprite_texture) {
        std::cerr << "Sprite wasn't loaded before function call";
        if (func_name != "") {
            std::cerr << " " << func_name;
        }
        std::cerr << "!" << std::endl;
        return true;
    }
    return false;
}


// Handle incoming events
void Player::handleEvent(const SDL_Event& e)
{
    if (noLoad("handleEvent")) return;

    // Handle keyboard events
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_LEFT) {
            m_info.x -= 10;
            if (m_info.x < 0) {
                m_info.x = 0;
            }
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
            m_info.x += 10;
            if (m_info.x > m_screen_surface->w - m_info.w) {
                m_info.x = m_screen_surface->w - m_info.w;
            }

        }
    }
}
