#include <iostream>
#include "SDL_image.h"
#include "game.hpp"

// Initialize the game with a window width and height, and a title
Game::Game(std::string title, int width, int height)
{
    m_inited = true;
    m_title = title;
    m_width = width;
    m_height = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        m_inited = false;
    }
    else
    {
        //Initialize PNG loading
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags))
        {
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
Game::~Game()
{
    close();
}

void Game::close()
{
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

void Game::loadFPSDisplay(double fps) {
    m_fps_string.str("");
    m_fps_string << fps;

    SDL_Color fps_color = { 0x00, 0xFF, 0x00, 0xFF };
    if (!m_fps_sprite->loadText(m_font, m_renderer, m_fps_string.str().c_str(), fps_color)) return;
    double fps_scale = m_height*0.0005;
    m_fps_sprite->setSize((int)(m_fps_sprite->getWidth()*fps_scale), (int)(m_fps_sprite->getHeight()*fps_scale));
    m_fps_sprite->setPosition(5, 5);
}

int Game::setup()
{
    m_window = SDL_CreateWindow(m_title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_width,
                                m_height,
                                SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
        std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Created window" << std::endl;

    // Get window renderer
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;
    if (m_vsync_enabled) renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
    m_renderer = SDL_CreateRenderer(m_window, -1, renderer_flags);
    if (m_renderer == NULL)
    {
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
    m_font = TTF_OpenFont(LoST_ASSETS_FONT_TITLE, LoST_ASSETS_FONT_TITLE_POINT);

    // Create a title
    Sprite* title_sprite = new Sprite();
    SDL_Color title_color = { 0xFF, 0xFF, 0xFF, 0xFF };
    if (!title_sprite->loadText(m_font, m_renderer, m_title.c_str(), title_color)) return 1;
    double title_scale = m_height*0.001;
    title_sprite->setSize((int)(title_sprite->getWidth()*title_scale), (int)(title_sprite->getHeight()*title_scale));
    title_sprite->setPosition((int)((m_width - title_sprite->getWidth())/2), (int)(m_height*0.1));

    // Create FPS counter
    m_fps_sprite = new Sprite();
    loadFPSDisplay(0.0);

    // Create a character sprite
    LoST_Player* player_sprite = new LoST_Player();
    SDL_Rect player_rect = {0};
    SDL_Rect player_collider = {0};
    int player_scale = (int)(m_height*0.0075);
    player_rect.w = player_sprite->getWidth()*player_scale;
    player_rect.h = player_sprite->getHeight()*player_scale;
    player_rect.x = (m_width - player_rect.w) / 2;
    player_rect.y = m_height - player_rect.h;
    player_sprite->getCollisionRect(&player_collider);
    player_collider.w *= player_scale;
    player_collider.h *= player_scale;
    player_collider.x *= player_scale;
    player_collider.y *= player_scale;
    if (!player_sprite->loadImage(LoST_ASSETS_PLAYER, m_renderer, &player_rect)) return 1;
    player_sprite->setCollisionRect(&player_collider);

    // Add sprites to sprite list
    m_sprite_list.push_back(title_sprite);
    m_sprite_list.push_back(player_sprite);

    // Start the fps timer
    m_counted_frames = 0;
    m_fps_timer.start();

    // Update the surface
    update();

    return 0;
}

void Game::update()
{
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

int Game::loop()
{
    if (!m_inited)
    {
        std::cerr << "Can't run game loop: SDL not inited" << std::endl;
        return 1;
    }

    // Allow the window to be drawn and wait for a quit event
    bool quit = false;
    SDL_Event e;

    // While the game is running
    while (!quit)
    {
        // Start framerate cap timer
        m_fps_cap_timer.start();

        // Handle events in the event queue
        while (SDL_PollEvent(&e))
        {
            // User asks to quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
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

    return 0;
}

void Game::capFPS(Uint32 fps) {
    m_fps_cap = fps;
    m_ms_per_frame = 1000.0 / m_fps_cap;
    enableVsync(false);
}

void Game::enableVsync(bool enable) {
    m_vsync_enabled = enable;
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, (enable ? "1" : "0"));
}
