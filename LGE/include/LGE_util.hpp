#ifndef LGE_UTIL_HPP__
#define LGE_UTIL_HPP__

#include <vector>
#include "SDL.h"

#define LGE_RECT_ASSIGN(_rect, _x, _y, _w, _h) do { \
    (_rect).x=_x; (_rect).y=_y; (_rect).w=_w; (_rect.h)=_h; \
} while(0)

namespace LGE {
    typedef SDL_Point Point;
    typedef SDL_Rect Rect;
    typedef SDL_Color Color;
};

#endif // LGE_UTIL_HPP__
