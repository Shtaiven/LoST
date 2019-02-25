#include <sstream>
#include "game.hpp"


// Software version constants
const char* SOFTWARE_NAME = "LoST";
const int 	SOFTWARE_VERSION_MAJOR = 1;
const int 	SOFTWARE_VERSION_MINOR = 0;
const int	SOFTWARE_VERSION_PATCH = 0;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// Entry point for the game
int main(int argc, char* args[]) {
	// Error code
	int err_code = 0;

	// Create window and title
	std::ostringstream window_title;
	window_title << SOFTWARE_NAME << " v"
				 << SOFTWARE_VERSION_MAJOR << "."
				 << SOFTWARE_VERSION_MINOR << "."
				 << SOFTWARE_VERSION_PATCH;
	
	Game game(window_title.str(), SCREEN_WIDTH, SCREEN_HEIGHT);

	err_code = game.setup();
	
	if (!err_code) {
		game.loop();
	}

	return err_code;
}
