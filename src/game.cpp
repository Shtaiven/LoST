#include "SDL_image.h"
#include <iostream>
#include <string>
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
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cerr << "Couldn't initialize SDL_image: " << IMG_GetError() << std::endl;
        }
        else
        {
            m_inited = true;
        }
    }

    // Clean up on exit
    atexit(SDL_Quit);
    atexit(IMG_Quit);
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
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == NULL)
    {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Created renderer" << std::endl;

    // Set renderer draw color to black
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Create a character sprite
    m_player = Player("../../assets/icon.png");
    SDL_Rect stretch = {0};
    stretch.w = 300;
    stretch.h = 300;
    m_player.load(&stretch);
    m_player.set_position((m_width - m_player.get_w()) / 2,
                          m_height - m_player.get_h());

    // Update the surface
    update();

    return 0;
}

void Game::update()
{
    // Fill the surface black
    SDL_RenderClear(m_renderer);

    // Render the player to the screen
    m_player.render(m_renderer);

    // Update the surface
    SDL_RendererFlip(m_renderer);
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
