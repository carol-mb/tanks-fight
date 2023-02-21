// game.c
#include "game.h"
#include "event.h"
#include "movement.h"
#include "render.h"

int main(int argc, char *argv[])
{
    TGameState *game = malloc(sizeof(TGameState));
    TTank *player = malloc(sizeof(TTank));

    player->movement_speed = 0;
    player->turret.rotation_angle = 0;

    game->player = player;

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS;

    SDL_Window* window = SDL_CreateWindow("TANKS FIGHT", // creates a window
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        window_flags);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
 
    // creates a renderer to render our images
    game->renderer = SDL_CreateRenderer(window, -1, render_flags);

    load_textures(game);
 
    // connects our texture with dest to control position
    SDL_QueryTexture(game->turret_texture, NULL, NULL, &player->turret.rect.w, &player->turret.rect.h);
    SDL_QueryTexture(game->body_texture, NULL, NULL, &player->body.rect.w, &player->body.rect.h);
    SDL_QueryTexture(game->playground_texture, NULL, NULL, &game->playground_rect.w, &game->playground_rect.h);

    // adjust height and width of our image box.
    game->playground_rect.w = PLAYGROUND_SIZE;
    game->playground_rect.h = PLAYGROUND_SIZE;

    player->turret.rect.w = PLAYER_SIZE;
    player->turret.rect.h = PLAYER_SIZE;

    player->turret.rect.w = TURRET_SIZE;
    player->turret.rect.h = TURRET_SIZE;
 
    // sets initial x-position of object
    player->x = (WINDOW_WIDTH - player->body.rect.w) / 2;

    // sets initial y-position of object
    player->y = (WINDOW_HEIGHT - player->body.rect.h) / 2;
 
    // controls animation loop
    int close = 0;
 
    // animation loop
    while (!close) { 
        close = handle_event(game);
        update_player_position(player);
        update_turret_position(player);

        game->playground_rect.x = player->body.rect.x - player->x;
        game->playground_rect.y = player->body.rect.y - player->y;

        render_game(game);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy textures
    destroy_textures(game);
 
    // destroy renderer
    SDL_DestroyRenderer(game->renderer);
 
    // destroy window
    SDL_DestroyWindow(window);
     
    // close SDL
    SDL_Quit();
    free(player);
    free(game);

    return 0;
}
