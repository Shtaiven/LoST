#include <iostream>
#include "SDL_image.h"
#include "LGE_engine.hpp"

// Initialize the game engine with a window width and height, and a title
LGE::Engine::Engine(std::string title, int width, int height) {
    m_inited = true;
    m_title = title;
    m_width = width;
    m_height = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        m_inited = false;
    } else {
        //Initialize PNG loading
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags)) {
            std::cerr << "Couldn't initialize SDL_image: " << IMG_GetError() << std::endl;
            m_inited = false;
        }

        // Initialize SDL_ttf
        if(TTF_Init() == -1) {
            std::cerr << "Couldn't initialize SDL_ttf: " << TTF_GetError() << std::endl;
            m_inited = false;
        }
    }
}

// Destructor
LGE::Engine::~Engine() {
    close();
}

void LGE::Engine::close() {
    // Stop fps timer
    m_fps_timer.stop();
    m_fps_cap_timer.stop();

    // Free textures
    for (int i = (int)m_sprite_list.size()-1; i >= 0; --i) {
        delete m_sprite_list[i];
    }
    m_sprite_list.clear();
    delete m_fps_sprite;

    // Free font
    TTF_CloseFont(m_font);
    m_font = NULL;

    // Destroy window
    SDL_DestroyWindow(m_window);
    m_window = NULL;

    // Destroy renderer
    SDL_DestroyRenderer(m_renderer);
    m_renderer = NULL;

    // Clean up on exit
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void LGE::Engine::init(init_t config) {
    m_config = config;
}

void LGE::Engine::loadFPSDisplay(double fps) {
    m_fps_string.str("");
    m_fps_string << fps;

    SDL_Color fps_color = { 0x00, 0xFF, 0x00, 0xFF };
    if (!m_fps_sprite->loadText(m_font, m_renderer, m_fps_string.str().c_str(), fps_color)) return;
    double fps_scale = m_height*0.0005;
    m_fps_sprite->setSize((int)(m_fps_sprite->getWidth()*fps_scale), (int)(m_fps_sprite->getHeight()*fps_scale));
    m_fps_sprite->setPosition(5, 5);
}

int LGE::Engine::setup() {
    int ret = 0;

    m_window = SDL_CreateWindow(m_title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_width,
                                m_height,
                                SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Created window" << std::endl;

    // Get window renderer
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;
    if (m_vsync_enabled) renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
    m_renderer = SDL_CreateRenderer(m_window, -1, renderer_flags);
    if (m_renderer == NULL) {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Created renderer" << std::endl;

    // Due to a bug up to SDL 2.0.9 on macOS 10.14, VSYNC doesn't work, so enable frame cap instead
    #ifdef __APPLE__
    if (!SDL_VERSION_ATLEAST(2, 0, 10)) {
        capFPS(60);
    }
    #endif // __APPLE__

    // Load font
    setFont(LGE_FONT_DEFAULT, LGE_FONT_POINT_DEFAULT);

    // Create FPS counter
    m_fps_sprite = new LGE::Sprite();
    loadFPSDisplay(0.0);

    if (m_config.setup) ret = m_config.setup();

    // Start the fps timer
    m_counted_frames = 0;
    m_fps_timer.start();

    // Update the surface
    update();

    return ret;
}

void LGE::Engine::update() {
    // Calculate and correct fps
    m_avg_fps = 0;
    m_last_update_ms = m_fps_timer.getTicks();
    if (m_last_update_ms) {
        m_avg_fps = m_counted_frames / ((double)m_last_update_ms / 1000.0);
        if (m_avg_fps > 2000000) {
            m_avg_fps = 0;
        }
    }

    // Load FPS texture
    loadFPSDisplay(m_avg_fps);

    // Fill the screen black
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_renderer);

    // Render all sprites to the screen
    for (int i = 0; i < m_sprite_list.size(); ++i) {
        m_sprite_list[i]->render();
    }

    // Render FPS to the screen
    if (m_display_fps) m_fps_sprite->render();

    // Update the screen
    SDL_RenderPresent(m_renderer);
}

int LGE::Engine::loop() {
    int ret = 0;

    if (!m_inited) {
        std::cerr << "Can't run game loop: SDL not inited" << std::endl;
        return 1;
    }

    // Allow the window to be drawn and wait for a quit event
    bool quit = false;
    SDL_Event e;

    // While the game is running
    while (!quit) {
        // Start framerate cap timer
        m_fps_cap_timer.start();

        // Handle events in the event queue
        while (SDL_PollEvent(&e)) {
            // User asks to quit
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                // Handle player events
                for (int i = 0; i < m_sprite_list.size(); ++i) {
                    m_sprite_list[i]->handleEvent(e);
                }
            }
        }

        // Calculate time since last update
        Uint32 current_ms = m_fps_timer.getTicks();
        Uint32 elapsed_time_ms = current_ms - m_last_update_ms;
        if (m_last_update_ms > current_ms) { // anticipate overflow
            elapsed_time_ms = (Uint32) (1000 / m_avg_fps);
        }

        // Handle player state
        for (int i = 0; i < m_sprite_list.size(); ++i) {
            m_sprite_list[i]->handleState(elapsed_time_ms);
        }

        if (m_config.loop) ret = m_config.loop();

        // Update game state and draw to window
        update();

        // Count the number of frames to calculate average FPS
        ++m_counted_frames;

        // Cap the framerate if vsync is disabled and fps cap is > 0
        if (!m_vsync_enabled && m_fps_cap > 0) {
            Uint32 ms_passed = m_fps_cap_timer.getTicks();
            if (ms_passed < m_ms_per_frame) {
                // Wait remaining time
                SDL_Delay((Uint32) m_ms_per_frame - ms_passed);
            }
        }
    }

    return ret;
}

int LGE::Engine::run() {
    int ret = 0;

    ret = LGE::Engine::setup();

    if (!ret) {
        ret = LGE::Engine::loop();
    }

    return ret;
}

void LGE::Engine::capFPS(Uint32 fps) {
    m_fps_cap = fps;
    m_ms_per_frame = 1000.0 / m_fps_cap;
    enableVsync(false);
}

void LGE::Engine::enableVsync(bool enable) {
    m_vsync_enabled = enable;
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, (enable ? "1" : "0"));
}

void LGE::Engine::addToSpriteList(LGE::Sprite *p_sprite) {
    m_sprite_list.push_back(p_sprite);
}

int LGE::Engine::getWidth() {
    return m_width;
}

int LGE::Engine::getHeight() {
    return m_height;
}

void LGE::Engine::setFont(char *ttf_file, int ptsize) {
    if (m_font) TTF_CloseFont(m_font);
    m_font = TTF_OpenFont(ttf_file, ptsize);
}
