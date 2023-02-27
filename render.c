#include "game.h"

void load_textures(TGameState *game) {    
    // please provide a path for your image
    SDL_Surface* body_surface = IMG_Load("./images/tank.png");
    SDL_Surface* grid_surface = IMG_Load("./images/grid.png");
    SDL_Surface* turret_surface = IMG_Load("./images/turret.png");
    SDL_Surface* bullet_surface = IMG_Load("./images/bullet.png");

    for (int i = 0; i < FOOD_TYPES; ++i) {
        char food_image[32];
        strcpy(food_image, "./images/food_");
        char buffer[2];
        strcpy(buffer, "0");
        buffer[0] += i;
        strcat(food_image, buffer);
        strcat(food_image, ".png");
        printf("%s\n", food_image);
        SDL_Surface* food_surface = IMG_Load(food_image);

        game->food_texture[i] = SDL_CreateTextureFromSurface(game->renderer, food_surface);

        SDL_FreeSurface(food_surface);
    }
 
    // loads image to our graphics hardware memory.
    game->body_texture = SDL_CreateTextureFromSurface(game->renderer, body_surface);
    game->playground_texture = SDL_CreateTextureFromSurface(game->renderer, grid_surface);
    game->turret_texture = SDL_CreateTextureFromSurface(game->renderer, turret_surface);
    game->bullet_texture = SDL_CreateTextureFromSurface(game->renderer, bullet_surface);
 
    // clears main-memory
    SDL_FreeSurface(body_surface);
    SDL_FreeSurface(grid_surface);
    SDL_FreeSurface(turret_surface);
    SDL_FreeSurface(bullet_surface);
}

void connect_textures(TGameState *game, TTank *player) {
    // connects our texture with dest to control position
    SDL_QueryTexture(game->turret_texture, NULL, NULL, &player->turret.rect.w, &player->turret.rect.h);
    SDL_QueryTexture(game->body_texture, NULL, NULL, &player->body.rect.w, &player->body.rect.h);
    SDL_QueryTexture(game->playground_texture, NULL, NULL, &game->playground_rect.w, &game->playground_rect.h);
}

void destroy_textures(TGameState* game) {
    SDL_DestroyTexture(game->turret_texture);
    SDL_DestroyTexture(game->body_texture);
    SDL_DestroyTexture(game->playground_texture);
    SDL_DestroyTexture(game->bullet_texture);
    for (int i = 0; i < FOOD_TYPES; ++i) {
        SDL_DestroyTexture(game->food_texture[i]);
    }
}

void render_game(TGameState *game) {
    // clears the screen
    SDL_RenderClear(game->renderer);

    SDL_RenderCopy(game->renderer, game->playground_texture, NULL, &game->playground_rect);

    for (int i = 0; i < game->max_bullets; ++i)
        if (game->bullets[i] != NULL)
            SDL_RenderCopy(game->renderer, game->bullet_texture, NULL, &game->bullets[i]->rect);

    SDL_RenderCopyEx(game->renderer,
                    game->turret_texture,
                    NULL,
                    &game->player->turret.rect,
                    game->player->turret.rotation_angle,
                    NULL,
                    SDL_FLIP_NONE);
    SDL_RenderCopy(game->renderer, game->body_texture, NULL, &game->player->body.rect);

    for (int i = 0; i < COLONIES_COUNT * COLONY_POPULATION; ++i) {
        if (game->food[i] != NULL) {
            SDL_RenderCopyEx(game->renderer,
                            game->food_texture[game->food[i]->type],
                            NULL,
                            &game->food[i]->rect,
                            game->food[i]->rotation_angle,
                            NULL, SDL_FLIP_NONE);
        }
    }
    
    // TTF_Font* Sans = TTF_OpenFont("/home/carol/tanks/sans.ttf", 24);
    // if (!Sans) printf("failed to load font\n");
    // SDL_Color White = {255, 255, 255};
    // SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White);
    // SDL_Texture* Message = SDL_CreateTextureFromSurface(game->renderer, surfaceMessage);

    // SDL_Rect Message_rect; //create a rect
    // Message_rect.x = 0;  //controls the rect's x coordinate 
    // Message_rect.y = 0; // controls the rect's y coordinte
    // Message_rect.w = 200; // controls the width of the rect
    // Message_rect.h = 24; // controls the height of the rect

    // SDL_RenderCopy(game->renderer, Message, NULL, &Message_rect);

    // SDL_FreeSurface(surfaceMessage);
    // SDL_DestroyTexture(Message);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(game->renderer);
}
