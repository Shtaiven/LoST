#include <iostream>
#include "SDL_image.h"
#include "game.hpp"

// Initialize the game with a window width and height, and a title
Game::Game(std::string title, int width, int height)
{
    m_inited = false;
    m_title = title;
    m_width = width;
    m_height = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    }
    else
    {
        //Initialize PNG loading
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags))
        {
            std::cerr << "Couldn't initialize SDL_image: " << IMG_GetError() << std::endl;
        }
        else
        {
            m_inited = true;
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
    // Destroy window
    SDL_DestroyWindow(m_window);
    m_window = NULL;

    // Destroy renderer
    SDL_DestroyRenderer(m_renderer);
    m_renderer = NULL;

    // Clean up on exit
    IMG_Quit();
    SDL_Quit();
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
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL)
    {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Created renderer" << std::endl;

    // Create a character sprite
    SDL_Rect player_info = {0};
    int player_scale = 5;
    player_info.w = LoST_ASSETS_PLAYER_FRAME_WIDTH*player_scale;
    player_info.h = LoST_ASSETS_PLAYER_FRAME_HEIGHT*player_scale;
    player_info.x = (m_width - player_info.w) / 2;
    player_info.y = m_height - player_info.h;
    if (!m_player.load(LoST_ASSETS_PLAYER, m_renderer, &player_info)) return 1;

    // Update the surface
    update();

    return 0;
}

void Game::update()
{
    // Fill the screen black
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_renderer);

    // Render the player to the screen
    m_player.render();

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
                // Handle player keyboard events
                m_player.handleEvent(e);
            }
        }

        // Update game state and draw to window
        update();
    }

    return 0;
}
