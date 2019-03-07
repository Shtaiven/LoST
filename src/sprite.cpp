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

    return true;
}


// Blit the sprite to the dst surface
void Sprite::blit(SDL_Surface* dst) {
    //Apply the image
    SDL_BlitSurface(m_sprite_surface, NULL, dst, NULL);
}
