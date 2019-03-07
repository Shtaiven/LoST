#include <iostream>
#include <string>
#include "game.hpp"


// Initialize the game with a window width and height, and a title
Game::Game(std::string title, int width, int height) {
    m_title = title;
    m_width = width;
    m_height = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    } else {
        m_inited = true;
    }

    // Clean up on exit
    atexit(SDL_Quit);
}


// Destructor
Game::~Game() {
    close();
}


void Game::close() {
    // Destroy window
    SDL_DestroyWindow(m_window);
    m_window = NULL;
}


int Game::setup() {
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

    // Get window surface
    m_screen_surface = SDL_GetWindowSurface(m_window);

    // Create a character sprite
    m_player = Player("../../assets/icon.bmp");
    m_player.load();

    // Update the surface
    update();

    return 0;
}


void Game::update() {
    // Fill the surface black
    SDL_FillRect(m_screen_surface, NULL, SDL_MapRGB(m_screen_surface->format, 0x00, 0x00, 0x00));

    // Blit the player to the screen
    m_player.blit(m_screen_surface);

    // Update the surface
    SDL_UpdateWindowSurface(m_window);
}


int Game::loop() {
    if (!m_inited) {
        std::cerr << "Can't run game loop: SDL not inited" << std::endl;
        return 1;
    }

    // Allow the window to be drawn and wait for a quit event
    bool quit = false;
    SDL_Event e;

    // While the game is running
    while (!quit) {
        // Handle events in the event queue
        while (SDL_PollEvent(&e)) {
            // User asks to quit
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                // Handle player keyboard events
                m_player.handleEvent(e);
            }
        }

        // Update game state and draw to window
        update();
    }

    return 0;
}