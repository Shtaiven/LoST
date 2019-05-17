#include <algorithm>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "sprite.hpp"

/* Sprite class methods *****************************************************/
Sprite::~Sprite() {
    free();
}

void Sprite::free() {
    if (m_texture) {
        // Deallocate the texture
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        memset(&m_render_rect, 0, sizeof(m_render_rect));
    }
}

void Sprite::loadTextureFromSurface(SDL_Surface* surface, SDL_Renderer* renderer, const SDL_Rect* render_rect) {
    // Remove previous texture
    free();

    // Optimize image performance
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!m_texture) {
        std::cerr << "Unable to create texture! SDL Error: "
                  << SDL_GetError()
                  << std::endl;
    }

    // Save info for later use during rendering
    setRenderRect(render_rect);
    m_renderer = renderer;
}

bool Sprite::loadImage(std::string file, SDL_Renderer* renderer, const SDL_Rect* render_rect) {
    // Load the sprite image
    SDL_Surface *temp_surface = IMG_Load(file.c_str());
    if (!temp_surface) {
        std::cerr << "Unable to load image from "
                  << file
                  << "! SDL_image Error: "
                  << IMG_GetError()
                  << std::endl;
    }
    loadTextureFromSurface(temp_surface, renderer, render_rect);

    // Free memory of temp_surface
    SDL_FreeSurface(temp_surface);

    return isLoaded();
}

bool Sprite::loadText(TTF_Font* font, SDL_Renderer* renderer, std::string text, const SDL_Color& color, const SDL_Point& pos) {
    // Load the text
    SDL_Surface *temp_surface = NULL;
    if (font) temp_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!temp_surface) {
        std::cerr << "Unable to load font! SDL_ttf Error: "
                  << TTF_GetError()
                  << std::endl;
    }

    SDL_Rect render_rect = {0};
    if (temp_surface) ASSIGN_SDL_RECT(render_rect, pos.x, pos.y, temp_surface->w, temp_surface->h);
    loadTextureFromSurface(temp_surface, renderer, &render_rect);

    // Free memory of temp_surface
    SDL_FreeSurface(temp_surface);

    return isLoaded();
}

// Render the sprite
int Sprite::render() {
    return SDL_RenderCopyEx(m_renderer, m_texture, m_clip, &m_render_rect, m_rotation, m_center, (SDL_RendererFlip) m_flip);
}

// Render the sprite to a specific location
int Sprite::render(int x, int y) {
    setPosition(x, y);
    return render();
}

void Sprite::getRenderRect(SDL_Rect* render_rect) {
    if (render_rect) memcpy(render_rect, &m_render_rect, sizeof(SDL_Rect));
}

void Sprite::setRenderRect(const SDL_Rect* render_rect) {
    if (render_rect) memcpy(&m_render_rect, render_rect, sizeof(SDL_Rect));
}

void Sprite::getCollisionRect(SDL_Rect* collision_rect) {
    if (collision_rect) memcpy(collision_rect, &m_collision_rect, sizeof(SDL_Rect));
}

void Sprite::setCollisionRect(const SDL_Rect* collision_rect) {
    if (collision_rect) memcpy(&m_collision_rect, collision_rect, sizeof(SDL_Rect));
}

void Sprite::setCenter(SDL_Point* center) {
    m_center = center;
}

int Sprite::getX() {
    return m_render_rect.x;
}

void Sprite::setX(int x) {
    m_render_rect.x = x;
}

int Sprite::getY() {
    return m_render_rect.y;
}

void Sprite::setY(int y) {
    m_render_rect.y = y;
}

void Sprite::setPosition(int x, int y) {
    setX(x); setY(y);
}

int Sprite::getWidth() {
    return m_render_rect.w;
}

void Sprite::setWidth(int w) {
    m_render_rect.w = w;
}

int Sprite::getHeight() {
    return m_render_rect.h;
}

void Sprite::setHeight(int h) {
    m_render_rect.h = h;
}

void Sprite::setSize(int w, int h) {
    setWidth(w); setHeight(h);
}

void Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

 void Sprite::setAlpha(Uint8 alpha) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void Sprite::setBlendMode(SDL_BlendMode blending) {
    //Set blending function
    SDL_SetTextureBlendMode(m_texture, blending);
}

Uint8 Sprite::getFlip() {
    return m_flip;
}

void Sprite::setFlip(Uint8 flip) {
    m_flip = flip & (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
}

double Sprite::getRotation() {
    return m_rotation;
}

void Sprite::setRotation(double angle) {
    m_rotation = angle;
}

void Sprite::clip(SDL_Rect* clip_rect) {
    m_clip = clip_rect;
}

bool Sprite::isLoaded() {
    return !!m_texture;
}

bool Sprite::checkCollision(const Sprite& a, const Sprite& b) {
    // The sides of the rectangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    // Calculate the sides of rect A
    left_a = a.m_collision_rect.x;
    right_a = a.m_collision_rect.x + a.m_collision_rect.w;
    top_a = a.m_collision_rect.y;
    bottom_a = a.m_collision_rect.y + a.m_collision_rect.h;

    // Calculate the sides of rect B
    left_b = b.m_collision_rect.x;
    right_b = b.m_collision_rect.x + b.m_collision_rect.w;
    top_b = b.m_collision_rect.y;
    bottom_b = b.m_collision_rect.y + b.m_collision_rect.h;

    // If any of the sides from A are within B, return true
    return !(bottom_a <= top_b ||
             top_a >= bottom_b ||
             right_a <= left_b ||
             left_a >= right_b);
}


/* AnimatedSprite class methods *********************************************/
AnimatedSprite::~AnimatedSprite() {
    m_frames.clear();
}

void AnimatedSprite::updateAnimationLen() {
    m_animation_len = 0;
    if (m_start_frame_index < m_end_frame_index) {
        m_animation_len = m_end_frame_index - m_start_frame_index + 1;
    }
}

size_t AnimatedSprite::nextFrameIndex() {
    size_t next_frame_index = m_current_frame_index;

    if (m_frame_delay >= 1) {
        ++m_frames_skipped %= m_frame_delay;
    }

    if (m_animation_len > 1 && !m_frames_skipped && m_frame_delay >= 0) {
        size_t next_frame_diff = m_current_frame_index - m_start_frame_index + 1;

        // If we haven't reached the end of the animation or we are looping, calculate the next frame
        if ((m_animation_len - next_frame_diff) || m_loop) {
            next_frame_index = next_frame_diff%m_animation_len + m_start_frame_index;
        }
    }
    return next_frame_index;
}

int AnimatedSprite::render() {
    if (m_current_frame_index >= numFrames()) return -1;
    clip(&m_frames[m_current_frame_index]);
    int result = Sprite::render();
    if (m_frame_delay >= 0) {
        m_current_frame_index = nextFrameIndex();
    }
    return result;
}

int AnimatedSprite::render(int x, int y) {
    setPosition(x, y);
    return render();
}

void AnimatedSprite::addFrame(int x, int y, int w, int h) {
    SDL_Rect frame = { x, y, w, h };
    addFrame(frame);
}

void AnimatedSprite::addFrame(const SDL_Rect& frame) {
    m_frames.push_back(frame);
    m_animation_len = numFrames();
}

void AnimatedSprite::addFrames(const std::vector<SDL_Rect>& frames) {
    m_frames.insert(m_frames.end(), frames.begin(), frames.end());
    m_animation_len = numFrames();
}

void AnimatedSprite::delFrames() {
    delFrames(numFrames());
}

void AnimatedSprite::delFrames(size_t n) {
    if (n > numFrames()) n = numFrames();
    m_frames.resize(numFrames()-n);
    m_animation_len = numFrames();
}

size_t AnimatedSprite::numFrames() {
    return m_frames.size();
}

void AnimatedSprite::getFrame(size_t index, SDL_Rect* buf) {
    if (buf && index < numFrames()) memcpy(buf, &m_frames[index], sizeof(SDL_Rect));
}

size_t AnimatedSprite::getCurrentFrameIndex() {
    return m_current_frame_index;
}

void AnimatedSprite::setCurrentFrameIndex(size_t index) {
    if (index >= numFrames()) {
        m_current_frame_index = numFrames();
    } else {
        m_current_frame_index = index;
    }
}

size_t AnimatedSprite::getStartFrameIndex() {
    return m_start_frame_index;
}

void AnimatedSprite::setStartFrameIndex(size_t index) {
    m_start_frame_index = index;
    updateAnimationLen();
}

size_t AnimatedSprite::getEndFrameIndex() {
    return m_end_frame_index;
}

void AnimatedSprite::setEndFrameIndex(size_t index) {
    m_end_frame_index = index;
    updateAnimationLen();
}

void AnimatedSprite::loop(bool loop) {
    m_loop = loop;
}

double AnimatedSprite::getSpeed() {
    double speed = 0.0;
    if (m_frame_delay >= 0) {
        speed = 1.0/(m_frame_delay+1);
    }

    return speed;
}

void AnimatedSprite::setSpeed(double speed) {
    if (speed < 1.0 && speed > 0) {;
        setFrameDelay((int)(1.0/speed-1));
    } else if (speed == 0.0) {
        setFrameDelay(-1);
    } else {
        setFrameDelay(0);
    }
}

int AnimatedSprite::getFrameDelay() {
    return m_frame_delay;
}

void AnimatedSprite::setFrameDelay(int delay) {
    m_frame_delay = std::max(delay, -1);
    m_frames_skipped = 0;
}
