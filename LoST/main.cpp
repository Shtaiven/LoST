#include <iostream>
#include "LoST.hpp"

// Entry point for the game
int main(int argc, char* args[]) {
    // Error code
    int err_code = 0;

    // Run the game
    err_code = LoST::Game::run();

    std::cout << "Exiting with code " << err_code << std::endl;
    return err_code;
}
