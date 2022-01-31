#if defined(MASH_PLOT_FEATURE)
#include "messages.hpp"
#include "plot.hpp"
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <sstream>

#include <iostream>

void cache_msg(const char *store, std::string *load);

static constexpr const Sint16 width = 800;
static constexpr const Sint16 height = 600;
static constexpr const Sint16 xparts = 24;
static constexpr const Sint16 identity = width / xparts;
static constexpr const Sint16 origo_x = width / 2;
static constexpr const Sint16 origo_y = height / 2;

#define WHITE       0xFF, 0xFF, 0xFF, 0xFF
#define LTGRAY      0xCC, 0xCC, 0xCC, 0xFF
#define BLACK       0x00, 0x00, 0x00, 0xFF
#define BLUE        0x00, 0x00, 0xFF, 0xFF

static void draw_board(SDL_Surface *window) {
    boxRGBA(window, 0, 0, width, height, WHITE);

    for (Sint16 i = origo_x; i <= width; i += identity)
        lineRGBA(window, i, 0, i, height, LTGRAY);

    for (Sint16 i = origo_y; i <= height; i += identity)
        lineRGBA(window, 0, i, width, i, LTGRAY);

    for (Sint16 i = origo_x; i >= 0; i -= identity)
        lineRGBA(window, i, 0, i, height, LTGRAY);

    for (Sint16 i = origo_y; i >= 0; i -= identity)
        lineRGBA(window, 0, i, width, i, LTGRAY);

    lineRGBA(window, 0, origo_y, width, origo_y, BLACK);
    lineRGBA(window, origo_x, 0, origo_x, height, BLACK);
    stringRGBA(window, 5, 5, "Press 'Q' to Quit", BLACK);
}

bool plot_function(mash::container& f) {
    static constexpr const double step = 0.0001;

    if (!f.is_valid()) {
        cache_msg(err_invalid_expression, nullptr);
        return false;
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *window  = SDL_SetVideoMode(width, height, 0, SDL_ANYFORMAT);
    if (window == nullptr) {
        cache_msg(err_window_open, nullptr);
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }

    SDL_WM_SetCaption("mash", "mash");

    draw_board(window);
    for (double i = -xparts - 1; i < xparts + 1; i += step) {
        const double f1 = f.evaluate(i);
        const double f2 = f.evaluate(i + step);
        const double i1 = i;
        const double i2 = i + step;
        lineRGBA(window, 
                 Sint16(i1 * identity + origo_x),
                 Sint16(-f1 * identity + origo_y),
                 Sint16(i2 * identity + origo_x),
                 Sint16(-f2 * identity + origo_y),
                 BLUE);
    }

    std::stringstream text;
    f->print(text);

    stringRGBA(window, origo_x + 5, 5, text.str().c_str(), BLACK);
    stringRGBA(window, width - 10, origo_y - 10, "x", BLACK);
    SDL_Flip(window);

    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
        const auto& symbol = event.key.keysym.sym;
        if (event.type == SDL_KEYDOWN && (symbol == 'q' || symbol == 'Q'))
            break;
    }
    SDL_Quit();
    return true;
}
#endif

