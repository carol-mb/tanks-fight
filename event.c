// event.c
#include "game.h"

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
            case SDL_SCANCODE_2:
                if (game->player->bullet_speed <= 5)
                    game->player->bullet_speed++;
            break;
            case SDL_SCANCODE_3:
                if (game->player->bullet_time <= 5)
                    game->player->bullet_time++;
            break;
            case SDL_SCANCODE_4:
                if (game->player->shooting_speed <= 5)
                    game->player->shooting_speed++;
            break;
            case SDL_SCANCODE_5:
                if (game->player->bullet_penetration <= 5)
                    game->player->bullet_penetration++;
            break;
            case SDL_SCANCODE_6:
                if (game->player->power <= 5)
                    game->player->power++;
            break;
            case SDL_SCANCODE_7:
                if (game->player->body_damage <= 5)
                    game->player->body_damage++;
            break;
            default:
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    game->player->shooting_style(game);
                break;
            }
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE]) {
        clock_t stop = clock();
        if (((double)(stop - game->player->last_shoot) / CLOCKS_PER_SEC) * 25 >= (DEFAULT_SHOOTING_SPEED - game->player->shooting_speed * SHOOT_TIME_BONUS))
            game->player->shooting_style(game);
    }

    return close;
}
