#include "render.h"

void load_textures(TGameState *game) {    
    // creates a surface to load an image into the main memory
    SDL_Surface* body_surface;
    SDL_Surface* grid_surface;
    SDL_Surface* turret_surface;
 
    // please provide a path for your image
    body_surface = IMG_Load("./images/tank.png");
    grid_surface = IMG_Load("./images/grid.png");
    turret_surface = IMG_Load("./images/turret.png");
 
    // loads image to our graphics hardware memory.
    game->body_texture = SDL_CreateTextureFromSurface(game->renderer, body_surface);
    game->playground_texture = SDL_CreateTextureFromSurface(game->renderer, grid_surface);
    game->turret_texture = SDL_CreateTextureFromSurface(game->renderer, turret_surface);
 
    // clears main-memory
    SDL_FreeSurface(body_surface);
    SDL_FreeSurface(grid_surface);
    SDL_FreeSurface(turret_surface);
}

void destroy_textures(TGameState* game) {
    SDL_DestroyTexture(game->turret_texture);
    SDL_DestroyTexture(game->body_texture);
    SDL_DestroyTexture(game->playground_texture);
}

void render_game(TGameState *game) {
    // clears the screen
    SDL_RenderClear(game->renderer);

    SDL_RenderCopy(game->renderer, game->playground_texture, NULL, &game->playground_rect);
    SDL_RenderCopyEx(game->renderer,
                    game->turret_texture,
                    NULL,
                    &game->player->turret.rect,
                    game->player->turret.rotation_angle,
                    NULL,
                    SDL_FLIP_NONE);
    SDL_RenderCopy(game->renderer, game->body_texture, NULL, &game->player->body.rect);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(game->renderer);
}
