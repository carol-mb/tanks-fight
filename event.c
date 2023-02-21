// event.c
#include "event.h"

int handle_event(TGameState* game) {
    SDL_Event event;
    int close = 0;
    // Events management
    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            // handling of close button
            close = 1;
            break;

        case SDL_KEYDOWN:
            // keyboard API for key pressed
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                close = 1;
                break;
            case SDL_SCANCODE_1:
                if (game->player->movement_speed <= 5)
                    game->player->movement_speed++;
                break;
            default:
                break;
            }
        }
    }
    return close;
}
