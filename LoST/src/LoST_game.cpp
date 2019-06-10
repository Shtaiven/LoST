#include <iostream>
#include <sstream>
#include "LGE.hpp"
#include "LoST_player.hpp"
#include "LoST_assets.hpp"
#include "LoST_game.hpp"

// Software version constants
const char* SOFTWARE_NAME = "LoST";
const int   SOFTWARE_VERSION_MAJOR = 0;
const int   SOFTWARE_VERSION_MINOR = 3;
const int   SOFTWARE_VERSION_PATCH = 0;

// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int LoST::Game::run() {
    // Create window and title
    std::ostringstream window_title;
    window_title << SOFTWARE_NAME << " v"
                 << SOFTWARE_VERSION_MAJOR << "."
                 << SOFTWARE_VERSION_MINOR << "."
                 << SOFTWARE_VERSION_PATCH;

    std::cout << "Starting " << window_title.str() << std::endl;
    LGE::Engine engine(window_title.str(), SCREEN_WIDTH, SCREEN_HEIGHT);

    // TODO: Reintroduce the sprites back into the game
    // // Create a title
    // LGE::Sprite* title_sprite = new LGE::Sprite();
    // SDL_Color title_color = { 0xFF, 0xFF, 0xFF, 0xFF };
    // if (!title_sprite->loadText(m_font, m_renderer, m_title.c_str(), title_color)) return 1;
    // double title_scale = m_height*0.001;
    // title_sprite->setSize((int)(title_sprite->getWidth()*title_scale), (int)(title_sprite->getHeight()*title_scale));
    // title_sprite->setPosition((int)((m_width - title_sprite->getWidth())/2), (int)(m_height*0.1));

    // // Create a character sprite
    // LoST::Player* player_sprite = new LoST::Player();
    // SDL_Rect player_rect = {0};
    // SDL_Rect player_collider = {0};
    // int player_scale = (int)(m_height*0.0075);
    // player_rect.w = player_sprite->getWidth()*player_scale;
    // player_rect.h = player_sprite->getHeight()*player_scale;
    // player_rect.x = (m_width - player_rect.w) / 2;
    // player_rect.y = m_height - player_rect.h;
    // player_sprite->getCollisionRect(&player_collider);
    // player_collider.w *= player_scale;
    // player_collider.h *= player_scale;
    // player_collider.x *= player_scale;
    // player_collider.y *= player_scale;
    // if (!player_sprite->loadImage(LoST_ASSETS_PLAYER, m_renderer, &player_rect)) return 1;
    // player_sprite->setCollisionRect(&player_collider);

    // // Add sprites to sprite list
    // m_sprite_list.push_back(title_sprite);
    // m_sprite_list.push_back(player_sprite);

    return engine.run();
}
