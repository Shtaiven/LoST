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
    // Free textures
    for (int i = m_sprite_list.size()-1; i >= 0; --i) {
        delete m_sprite_list[i];
    }
    m_sprite_list.clear();

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

    // Create a title
    Sprite* title_sprite = new Sprite();
    m_font = TTF_OpenFont(LoST_ASSETS_FONT_TITLE, LoST_ASSETS_FONT_TITLE_POINT);
    SDL_Color title_color = { 0xFF, 0xFF, 0xFF, 0xFF };
    if (!title_sprite->loadText(m_font, m_renderer, m_title.c_str(), title_color)) return 1;
    double title_scale = m_height*0.001;
    title_sprite->setSize(title_sprite->getWidth()*title_scale, title_sprite->getHeight()*title_scale);
    title_sprite->setPosition((m_width - title_sprite->getWidth())/2, m_height*0.1);

    // Create a character sprite
    LoST_Player* player_sprite = new LoST_Player();
    SDL_Rect player_rect = {0};
    int player_scale = m_height*0.0075;
    player_rect.w = LoST_ASSETS_PLAYER_FRAME_WIDTH*player_scale;
    player_rect.h = LoST_ASSETS_PLAYER_FRAME_HEIGHT*player_scale;
    player_rect.x = (m_width - player_rect.w) / 2;
    player_rect.y = m_height - player_rect.h;
    if (!player_sprite->loadImage(LoST_ASSETS_PLAYER, m_renderer, &player_rect)) return 1;

    // Add sprites to sprite list
    m_sprite_list.push_back(title_sprite);
    m_sprite_list.push_back(player_sprite);

    // Update the surface
    update();

    return 0;
}

void Game::update()
{
    // Fill the screen black
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_renderer);

    // Render all sprites to the screen
    for (int i = 0; i < m_sprite_list.size(); ++i) {
        m_sprite_list[i]->render();
    }

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
                // Handle player events
                for (int i = 0; i < m_sprite_list.size(); ++i) {
                    m_sprite_list[i]->handleEvent(e);
                }
            }
        }

        // Update game state and draw to window
        update();
    }

    return 0;
}
