#include <algorithm>
#include "SDL_image.h"
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
    return !m_texture;
}


/* AnimatedSprite class methods *********************************************/
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

    if (m_animation_len && !m_frames_skipped && m_frame_delay >= 0) {
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
    int result = Sprite::render(&m_frames[m_current_frame_index]);
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

float AnimatedSprite::getSpeed() {
    float speed = 0.0;
    if (m_frame_delay >= 0) {
        speed = 1.0/(m_frame_delay+1);
    }

    return speed;
}

void AnimatedSprite::setSpeed(float speed) {
    if (speed < 1.0 && speed > 0) {;
        setFrameDelay(1.0/speed-1);
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
