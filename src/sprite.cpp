#include "SDL_image.h"
#include "sprite.hpp"


Sprite::Sprite() {}


Sprite::~Sprite() {
    free();
}


void Sprite::free() {
    if (m_texture) {
        // Deallocate the texture
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        memset(&m_info, 0, sizeof(m_info));
    }
}


bool Sprite::load(std::string file, SDL_Renderer* renderer, const SDL_Rect* info) {
    // Remove previous texture
    free();

    // Load the sprite image
    SDL_Surface *temp_surface = IMG_Load(file.c_str());
    if (!temp_surface) {
        std::cerr << "Unable to load image from "
                  << file
                  << "! SDL_image Error: "
                  << IMG_GetError()
                  << std::endl;
    }

    // Optimize image performance
    m_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    if (!m_texture) {
        std::cerr << "Unable to create texture from "
                  << file
                  << "! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
    }

    // Free memory of temp_surface
    SDL_FreeSurface(temp_surface);

    // Save info for later use during rendering
    if (info) setInfo(info);
    m_renderer = renderer;

    return (bool) m_texture;
}


// Render the sprite
int Sprite::render(const SDL_Rect* clip) {
    return SDL_RenderCopy(m_renderer, m_texture, clip, &m_info);
}


// Render the sprite to a specific location
int Sprite::render(int x, int y, const SDL_Rect* clip) {
    setPosition(x, y);
    return render(clip);
}


void Sprite::getInfo(SDL_Rect* buf) {
    if (buf) memcpy(buf, &m_info, sizeof(SDL_Rect));
}


void Sprite::setInfo(const SDL_Rect* info) {
    if (info) memcpy(&m_info, info, sizeof(SDL_Rect));
}


void Sprite::setPosition(int x, int y) {
    m_info.x = x;
    m_info.y = y;
}


void Sprite::setPosition(const SDL_Rect* pos) {
    if (pos) setPosition(pos->x, pos->y);
}


void Sprite::setSize(int w, int h) {
    m_info.w = w;
    m_info.h = h;
}


void Sprite::setSize(const SDL_Rect* size) {
    if (size) setSize(size->w, size->h);
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
