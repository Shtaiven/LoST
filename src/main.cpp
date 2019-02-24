#include <cstdio>
#include <cstdlib>
#include "SDL.h"
#include "game.hpp"

// Software version constants
const char* SOFTWARE_NAME = "LoST";
const int 	SOFTWARE_VERSION_MAJOR = 1;
const int 	SOFTWARE_VERSION_MINOR = 0;
const int	SOFTWARE_VERSION_PATCH = 0;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// The surface contained by the window
	SDL_Surface* screen = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
	}

	// Clean up on exit
	atexit(SDL_Quit);

	// Create window and title
	char windowTitle[256] = {0};
	sprintf(windowTitle, "%s v%d.%d.%d",
			SOFTWARE_NAME,
		    SOFTWARE_VERSION_MAJOR,
			SOFTWARE_VERSION_MINOR,
			SOFTWARE_VERSION_PATCH);
	window = SDL_CreateWindow(windowTitle,
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  SCREEN_WIDTH,
							  SCREEN_HEIGHT,
							  SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
		exit(1);
	}

	// Get window surface
	screen = SDL_GetWindowSurface(window);

	// Fill the surface black
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	
	// Update the surface
	SDL_UpdateWindowSurface(window);

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

	// Destroy window
	SDL_DestroyWindow(window);

	return 0;
}