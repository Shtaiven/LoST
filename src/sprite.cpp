#include "SDL_image.h"
#include "sprite.hpp"


Sprite::Sprite() {}


Sprite::~Sprite() {
    close();
}


void Sprite::close() {
    // Deallocate the texture
    SDL_DestroyTexture(m_texture);
    m_texture = NULL;
}


bool Sprite::load(std::string file, SDL_Renderer* renderer, const SDL_Rect* info) {
    bool result = true;

    // Load the sprite image
    SDL_Surface *temp_surface = IMG_Load(file.c_str());
    if (!temp_surface) {
        std::cerr << "Unable to load image from "
                  << file
                  << "! SDL_image Error: "
                  << IMG_GetError()
                  << std::endl;
        result = false;
    }

    // Optimize image performance
    m_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    if (!m_texture) {
        std::cerr << "Unable to create texture from "
                  << file
                  << "! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
        result = false;
    }

    // Free memory of temp_surface
    SDL_FreeSurface(temp_surface);

    // Save info for later use during rendering
    if (info) set_info(info);
    m_renderer = renderer;

    return result;
}


// Blit the sprite to the dst surface
void Sprite::render() {
    if (noLoad("render")) return;

    //Apply the image
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_info);
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
    if (!m_texture) {
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
        int max_w, max_h;
        SDL_GetRendererOutputSize(m_renderer, &max_w, &max_h);

        if (e.key.keysym.sym == SDLK_LEFT) {
            m_info.x -= 10;
            if (m_info.x < 0) {
                m_info.x = 0;
            }
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
            m_info.x += 10;
            if (m_info.x > max_w - m_info.w) {
                m_info.x = max_w - m_info.w;
            }

        }
    }
}
