#include <iostream>
#include <string>
#include "game.hpp"

Game::Game(std::string title, int width, int height) {
    m_title = title;
    m_window = NULL;
    m_screen = NULL;
    m_width = width;
    m_height = height;
    m_inited = true;
    m_quit = false;

    // Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        m_inited = false;
	}

    // Clean up on exit
	atexit(SDL_Quit);
}

Game::~Game() {
    if (!m_inited) {
        return;
    }

    // Destroy window
    SDL_DestroyWindow(m_window);
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

	// Get window surface
	m_screen = SDL_GetWindowSurface(m_window);

	// Fill the surface black
	SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, 0x00, 0x00, 0x00));
	
	// Update the surface
	SDL_UpdateWindowSurface(m_window);

    return 0;
}

int Game::loop() {
    if (!m_inited) {
        std::cerr << "Can't run game loop: SDL not inited" << std::endl;
        return 1;
    }

	// Allow the window to be drawn and wait for a quit event
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

    return 0;
}