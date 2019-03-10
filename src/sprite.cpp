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

    // Deallocate the stretch rect
    free(m_stretch_rect);
    m_stretch_rect = NULL;
}


bool Sprite::load(SDL_Surface* screen_surface, const SDL_Rect* stretch_rect, int x, int y) {
    bool result = true;

    // Load the sprite image
    SDL_Surface *temp_surface = SDL_LoadBMP(m_file.c_str());
    if (!temp_surface) {
        std::cerr << "Unable to load image "
                  << m_file
                  << "! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
        result = false;
    }

    // Optimize image performance
    m_sprite_surface = SDL_ConvertSurface(temp_surface, screen_surface->format, NULL);
    if (!m_sprite_surface) {
        std::cerr << "Unable to optimize image "
                  << m_file
                  << "! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
        result = false;
    }

    // Free memory of temp_surface and store new surface
    SDL_FreeSurface(temp_surface);
    m_screen_surface = screen_surface;
    if (stretch_rect) {
        m_stretch_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        memcpy(m_stretch_rect, stretch_rect, sizeof(SDL_Rect));
    }

    if (m_stretch_rect) {
        m_rect.w = m_stretch_rect->w;
        m_rect.h = m_stretch_rect->h;
        m_rect.x = x;
        m_rect.y = y;
    } else {
        m_rect.w = m_sprite_surface->w;
        m_rect.h = m_sprite_surface->h;
        m_rect.x = x;
        m_rect.y = y;
    }

    return result;
}


// Blit the sprite to the dst surface
void Sprite::blit() {
    if (screenSurfaceNull("blit")) return;

    //Apply the image
    if (m_stretch_rect) {
        m_stretch_rect->x = m_rect.x;
        m_stretch_rect->y = m_rect.y;
        SDL_BlitScaled(m_sprite_surface, NULL, m_screen_surface, m_stretch_rect);
    } else {
        SDL_BlitSurface(m_sprite_surface, NULL, m_screen_surface, &m_rect);
    }
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

bool Sprite::screenSurfaceNull(std::string func) {
    if (!m_screen_surface) {
        std::cerr << "Sprite wasn't loaded before function call";
        if (func != "") {
            std::cerr << " " << func;
        }
        std::cerr << "!" << std::endl;
        return true;
    }
    return false;
}

// Handle incoming events
void Player::handleEvent(const SDL_Event& e)
{
    if (screenSurfaceNull("handleEvent")) return;

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
            if (m_rect.x > m_screen_surface->w - m_rect.w) {
                m_rect.x = m_screen_surface->w - m_rect.w;
            }

        }
    }
}
