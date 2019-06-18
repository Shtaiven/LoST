#include <algorithm>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "LGE_util.hpp"
#include "LGE_sprite.hpp"


/* Sprite class methods *****************************************************/
LGE::Sprite::~Sprite() {
    free();
}

void LGE::Sprite::free() {
    if (m_texture) {
        // Deallocate the texture
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        memset(&m_render_rect, 0, sizeof(m_render_rect));
    }
}

void LGE::Sprite::loadTextureFromSurface(SDL_Surface* surface, SDL_Renderer* renderer, const SDL_Rect* render_rect) {
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

bool LGE::Sprite::loadImage(std::string file, SDL_Renderer* renderer, const SDL_Rect* render_rect) {
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

bool LGE::Sprite::loadText(TTF_Font* font, SDL_Renderer* renderer, std::string text, const SDL_Color& color, const SDL_Point& pos) {
    // Load the text
    SDL_Surface *temp_surface = NULL;
    if (font) temp_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!temp_surface) {
        std::cerr << "Unable to load font! SDL_ttf Error: "
                  << TTF_GetError()
                  << std::endl;
    }

    SDL_Rect render_rect = {0};
    if (temp_surface) LGE_RECT_ASSIGN(render_rect, pos.x, pos.y, temp_surface->w, temp_surface->h);
    loadTextureFromSurface(temp_surface, renderer, &render_rect);

    // Free memory of temp_surface
    SDL_FreeSurface(temp_surface);

    return isLoaded();
}

// Render the sprite
int LGE::Sprite::render() {
    int ret = SDL_RenderCopyEx(m_renderer, m_texture, m_clip, &m_render_rect, m_rotation, m_center, (SDL_RendererFlip) m_flip);
    if (m_collision_debug && hasCollision()) {
        SDL_Rect displaced_collision_rect = {
            m_render_rect.x + m_collision_rect.x,
            m_render_rect.y + m_collision_rect.y,
            m_collision_rect.w,
            m_collision_rect.h
        };
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(m_renderer, &displaced_collision_rect);
    }
    return ret;
}

// Render the sprite to a specific location
int LGE::Sprite::render(int x, int y) {
    setPosition(x, y);
    return render();
}

void LGE::Sprite::getRenderRect(SDL_Rect* render_rect) {
    if (render_rect) memcpy(render_rect, &m_render_rect, sizeof(SDL_Rect));
}

void LGE::Sprite::setRenderRect(const SDL_Rect* render_rect) {
    if (render_rect) memcpy(&m_render_rect, render_rect, sizeof(SDL_Rect));
}

void LGE::Sprite::getCollisionRect(SDL_Rect* collision_rect) {
    if (collision_rect) memcpy(collision_rect, &m_collision_rect, sizeof(SDL_Rect));
}

void LGE::Sprite::setCollisionRect(const SDL_Rect* collision_rect) {
    if (collision_rect) memcpy(&m_collision_rect, collision_rect, sizeof(SDL_Rect));
}

void LGE::Sprite::setCenter(SDL_Point* center) {
    m_center = center;
}

int LGE::Sprite::getX() {
    return m_render_rect.x;
}

void LGE::Sprite::setX(int x) {
    m_render_rect.x = x;
}

int LGE::Sprite::getY() {
    return m_render_rect.y;
}

void LGE::Sprite::setY(int y) {
    m_render_rect.y = y;
}

void LGE::Sprite::setPosition(int x, int y) {
    setX(x); setY(y);
}

int LGE::Sprite::getWidth() {
    return m_render_rect.w;
}

void LGE::Sprite::setWidth(int w) {
    m_render_rect.w = w;
}

int LGE::Sprite::getHeight() {
    return m_render_rect.h;
}

void LGE::Sprite::setHeight(int h) {
    m_render_rect.h = h;
}

void LGE::Sprite::setSize(int w, int h) {
    setWidth(w); setHeight(h);
}

void LGE::Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

 void LGE::Sprite::setAlpha(Uint8 alpha) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void LGE::Sprite::setBlendMode(SDL_BlendMode blending) {
    //Set blending function
    SDL_SetTextureBlendMode(m_texture, blending);
}

Uint8 LGE::Sprite::getFlip() {
    return m_flip;
}

void LGE::Sprite::setFlip(Uint8 flip) {
    m_flip = flip & (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
}

double LGE::Sprite::getRotation() {
    return m_rotation;
}

void LGE::Sprite::setRotation(double angle) {
    m_rotation = angle;
}

void LGE::Sprite::clip(SDL_Rect* clip_rect) {
    m_clip = clip_rect;
}

bool LGE::Sprite::isLoaded() {
    return !!m_texture;
}

bool LGE::Sprite::hasCollision() {
    return (m_collision_rect.w || m_collision_rect.h);
}

bool LGE::Sprite::checkCollision(Sprite* a, Sprite* b) {
    // TODO: Be able to check combinations of multiple circular or rectangular colliders
    // If a or b has no dimension, return false
    if (!a->hasCollision() || !b->hasCollision())
    {
        return false;
    }

    // The sides of the rectangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    // Calculate the sides of rect A
    left_a = a->m_collision_rect.x + a->m_render_rect.x;
    right_a = left_a + a->m_collision_rect.w;
    top_a = a->m_collision_rect.y + a->m_render_rect.y;
    bottom_a = top_a + a->m_collision_rect.h;

    // Calculate the sides of rect B
    left_b = b->m_collision_rect.x + b->m_render_rect.x;
    right_b = left_b + b->m_collision_rect.w;
    top_b = b->m_collision_rect.y + b->m_render_rect.y;
    bottom_b = top_b + b->m_collision_rect.h;

    // If any of the sides from A are within B, return true
    return !(bottom_a <= top_b ||
             top_a >= bottom_b ||
             right_a <= left_b ||
             left_a >= right_b);
}

void LGE::Sprite::addEventHandler(SpriteEventHandler handler) {
    m_event_handlers.push_back(handler);
}

void LGE::Sprite::removeEventHandler(SpriteEventHandler handler) {
    int h;
    for (h=0; h < m_event_handlers.size(); ++h) {
        if (m_event_handlers[h] == handler) {
            m_event_handlers.erase(m_event_handlers.begin()+h);
        }
    }
}

void LGE::Sprite::handleEvent(const SDL_Event& e) {
    int h;
    for (h=0; h < m_event_handlers.size(); ++h) {
        m_event_handlers[h](e);
    }
}

void LGE::Sprite::addStateHandler(SpriteStateHandler handler) {
    m_state_handlers.push_back(handler);
}

void LGE::Sprite::removeStateHandler(SpriteStateHandler handler) {
    int h;
    for (h=0; h < m_state_handlers.size(); ++h) {
        if (m_state_handlers[h] == handler) {
            m_state_handlers.erase(m_state_handlers.begin()+h);
        }
    }
}

void LGE::Sprite::handleState(Uint32 ms) {
    int h;
    for (h=0; h < m_state_handlers.size(); ++h) {
        m_state_handlers[h](ms);
    }
}


/* AnimatedSprite class methods *********************************************/
LGE::AnimatedSprite::~AnimatedSprite() {
    m_frames.clear();
}

void LGE::AnimatedSprite::updateAnimationLen() {
    m_animation_len = 0;
    if (m_start_frame_index < m_end_frame_index) {
        m_animation_len = m_end_frame_index - m_start_frame_index + 1;
    }
}

size_t LGE::AnimatedSprite::calculateNextFrame() {
    size_t next_frame_diff = m_current_frame_index - m_start_frame_index + 1;

    // If we haven't reached the end of the animation or we are looping, calculate the next frame
    if ((m_animation_len - next_frame_diff) || m_loop) {
        return next_frame_diff%m_animation_len + m_start_frame_index;
    }

    return m_current_frame_index;
}

size_t LGE::AnimatedSprite::nextFrameIndex() {
    size_t next_frame_index = m_current_frame_index;
    if (!m_frame_rate) {  // use undefined framerate method
        if (m_frame_delay >= 1) {
            ++m_frames_skipped %= m_frame_delay;
        }

        if (m_animation_len > 1 && !m_frames_skipped && m_frame_delay >= 0) {
            next_frame_index = calculateNextFrame();
        }
    } else if (m_frame_rate > 0) {  // use positive framerate method
        int ms_per_frame = (int)(1.0 / m_frame_rate * 1000.0 / getSpeed());
        if (m_animation_len > 1 && (size_t) m_time_elapsed_ms >= ms_per_frame) {
            int n_frames = m_time_elapsed_ms / ms_per_frame; // number of frames ahead to calculate in case of skipped frames
            m_time_elapsed_ms %= ms_per_frame;
            // printf("ms_per_frame: %d, n_frames: %d, m_time_elapsed_ms: %d\n", ms_per_frame, n_frames, m_time_elapsed_ms);
            int i;
            for (i = 0; i < n_frames; ++i) {
                next_frame_index = calculateNextFrame();
            }
        }
    }
    return next_frame_index;
}

int LGE::AnimatedSprite::render() {
    if (m_current_frame_index >= numFrames()) return -1;
    clip(&m_frames[m_current_frame_index]);
    int result = Sprite::render();
    m_current_frame_index = nextFrameIndex();
    return result;
}

int LGE::AnimatedSprite::render(int x, int y) {
    setPosition(x, y);
    return render();
}

void LGE::AnimatedSprite::addFrame(int x, int y, int w, int h) {
    SDL_Rect frame = { x, y, w, h };
    addFrame(frame);
}

void LGE::AnimatedSprite::addFrame(const SDL_Rect& frame) {
    m_frames.push_back(frame);
    m_animation_len = numFrames();
}

void LGE::AnimatedSprite::addFrames(const std::vector<SDL_Rect>& frames) {
    m_frames.insert(m_frames.end(), frames.begin(), frames.end());
    m_animation_len = numFrames();
}

void LGE::AnimatedSprite::delFrames() {
    delFrames(numFrames());
}

void LGE::AnimatedSprite::delFrames(size_t n) {
    if (n > numFrames()) n = numFrames();
    m_frames.resize(numFrames()-n);
    m_animation_len = numFrames();
}

size_t LGE::AnimatedSprite::numFrames() {
    return m_frames.size();
}

void LGE::AnimatedSprite::getFrame(size_t index, SDL_Rect* buf) {
    if (buf && index < numFrames()) memcpy(buf, &m_frames[index], sizeof(SDL_Rect));
}

size_t LGE::AnimatedSprite::getCurrentFrameIndex() {
    return m_current_frame_index;
}

void LGE::AnimatedSprite::setCurrentFrameIndex(size_t index) {
    if (index >= numFrames()) {
        m_current_frame_index = numFrames();
    } else {
        m_current_frame_index = index;
    }
}

size_t LGE::AnimatedSprite::getStartFrameIndex() {
    return m_start_frame_index;
}

void LGE::AnimatedSprite::setStartFrameIndex(size_t index) {
    m_start_frame_index = index;
    updateAnimationLen();
}

size_t LGE::AnimatedSprite::getEndFrameIndex() {
    return m_end_frame_index;
}

void LGE::AnimatedSprite::setEndFrameIndex(size_t index) {
    m_end_frame_index = index;
    updateAnimationLen();
}

void LGE::AnimatedSprite::loop(bool loop) {
    m_loop = loop;
}

double LGE::AnimatedSprite::getSpeed() {
    double speed = 0.0;
    if (m_frame_delay >= 0) {
        speed = 1.0/(m_frame_delay+1);
    }

    return speed;
}

void LGE::AnimatedSprite::setSpeed(double speed) {
    if (speed < 1.0 && speed > 0) {;
        setFrameDelay((int)(1.0/speed-1));
    } else if (speed == 0.0) {
        setFrameDelay(-1);
    } else {
        setFrameDelay(0);
    }
}

int LGE::AnimatedSprite::getFrameDelay() {
    return m_frame_delay;
}

void LGE::AnimatedSprite::setFrameDelay(int delay) {
    m_frame_delay = std::max(delay, -1);
    m_frames_skipped = 0;
}

int LGE::AnimatedSprite::getFrameRate() {
    return m_frame_rate;
}

void LGE::AnimatedSprite::setFrameRate(int frames_per_second) {
    m_frame_rate = frames_per_second;
}

void LGE::AnimatedSprite::adjustTimeElapsed(int ms) {
    m_time_elapsed_ms += ms;
}
