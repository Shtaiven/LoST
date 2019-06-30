#ifndef LGE_ENGINE_HPP__
#define LGE_ENGINE_HPP__

#include <string>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "LGE_timer.hpp"
#include "LGE_sprite.hpp"

#ifdef _WIN32
    #define LGE_ROOT_DIR "../../../"
#else
    #define LGE_ROOT_DIR "../../"
#endif // _WIN32
#define LGE_ASSETS_DIR LGE_ROOT_DIR "LGE/assets/"
#define LGE_FONT_DIR LGE_ASSETS_DIR "fonts/"
#define LGE_FONT_DEFAULT LGE_FONT_DIR "Open_Sans/OpenSans-Regular.ttf"
#define LGE_FONT_POINT_DEFAULT 96

namespace LGE {

class Engine {
public:
    typedef int (*InitFunc)();
    typedef struct InitType {
        InitFunc setup;
        InitFunc loop;
    } InitType;
    Engine(std::string title="Untitled", int width=640, int height=480);
    ~Engine();
    int init(InitType config={0, 0});
    int setup();
    int loop();
    int run();
    void close();
    void update();
    void capFPS(Uint32 fps);
    void enableVsync(bool enable);
    void addSprite(LGE::Sprite *p_sprite);
    int getWidth();
    int getHeight();
    std::string getTitle();
    SDL_Renderer* getRenderer();
    void setFont(std::string ttf_file, int ptsize);


private:
    // Window and rendering
    SDL_Window* m_window = NULL;
    SDL_Renderer* m_renderer = NULL;
    bool m_quit = false;
    bool m_inited = false;
    int m_width;
    int m_height;

    // Game information and display
    std::string m_title;
    TTF_Font* m_font = NULL;
    std::vector<LGE::Sprite*> m_sprite_list;

    // Framerate
    InitType m_config = {0};
    bool m_vsync_enabled = true;
    Uint32 m_fps_cap = 0;
    double m_ms_per_frame = 0;
    LGE::Timer m_fps_cap_timer;
    Uint32 m_counted_frames;
    Uint32 m_last_update_ms;
    double m_avg_fps;
    LGE::Timer m_fps_timer;
    LGE::Sprite* m_fps_sprite = NULL;
    std::stringstream m_fps_string;
    bool m_display_fps = true;
    void loadFPSDisplay(double fps);
};

}

#endif // LGE_ENGINE_HPP__
