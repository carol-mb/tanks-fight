// game.c
#include "game.h"
#include "event.h"
#include "movement.h"
#include "render.h"
#include "food.h"
#include "combat.h"
#include "collision.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    TGameState *game = (TGameState*)malloc(sizeof(TGameState));
    TTank *player = (TTank*)malloc(sizeof(TTank));

    player->movement_speed = 0;
    player->bullet_speed = 0;
    player->bullet_time = 0;
    player->turret.rotation_angle = 0;
    player->last_shoot = 0;
    player->shooting_speed = 0;
    player->bullet_penetration = 0;
    player->power = 0;

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
    for (int i = 0; i < FOOD_TYPES; ++i)
        game->food_texture[i] = NULL; 
    game->body_texture = NULL;
    game->turret_texture = NULL;
    game->playground_texture = NULL;
    game->bullet_texture = NULL;
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
    
    player->dx = 0;
    player->dy = 0;

    // controls animation loop
    int close = 0;
    
    game->remaining_food = 0;
    for (int i = 0; i < COLONIES_COUNT * COLONY_POPULATION; ++i)
        game->food[i] = NULL;
    for (int i = 0; i < COLONIES_COUNT; ++i)
        generate_new_colony(game);

    game->max_bullets = 2;
    game->bullets = (TBullet**)malloc(game->max_bullets * sizeof(TBullet*));
    game->player->shooting_style = default_shoot;

    for (int i = 0; i < game->max_bullets; ++i) {
        game->bullets[i] = NULL;
    }

    // animation loop
    while (!close) { 
        close = handle_event(game);
        update_player_position(player);
        update_turret_position(player);

        if (game->remaining_food + COLONY_POPULATION <= COLONIES_COUNT * COLONY_POPULATION) {
            printf("new colony\n");
            generate_new_colony(game);
        }

        game->playground_rect.x = player->body.rect.x - player->x;
        game->playground_rect.y = player->body.rect.y - player->y;
        for (int i = 0; i < COLONIES_COUNT * COLONY_POPULATION; ++i) {
            if (game->food[i] != NULL) {
                if(check_collision(player->x, player->y, PLAYER_SIZE, PLAYER_SIZE,
                                    game->food[i]->x, game->food[i]->y, game->food[i]->rect.w, game->food[i]->rect.h)) {
                    game->food[i]->health -= (DEFAULT_BODY_DAMAGE + player->body_damage * BODY_DAMAGE_BONUS);
                    printf("BODY HIT! New food health %d\n", game->food[i]->health);
                    player->dx *= 0.75f;
                    player->dy *= 0.75f;
                    game->food[i]->dx += player->dx;
                    game->food[i]->dy += player->dy;
                    if (game->food[i]->health <= 0) {
                        free(game->food[i]);
                        game->food[i] = NULL;
                        game->remaining_food--;
                        continue;
                    }
                }

                game->food[i]->x += game->food[i]->dx;
                game->food[i]->y += game->food[i]->dy;
                game->food[i]->rect.x = game->food[i]->x + (WINDOW_WIDTH / 2 - player->x);
                game->food[i]->rect.y = game->food[i]->y + (WINDOW_HEIGHT / 2 - player->y);

                game->food[i]->dx *= 0.95f;
                if (fabs(game->food[i]->dx) < 0.0001f)
                    game->food[i]->dy = 0;
                
                game->food[i]->dy *= 0.95f;
                if (fabs(game->food[i]->dy) < 0.0001f)
                    game->food[i]->dy = 0;
            }
        }

        for (int i = 0; i < game->max_bullets; ++i) {
            if (game->bullets[i] != NULL) {
                update_bullet_position(game->bullets[i]);
                game->bullets[i]->rect.x = game->bullets[i]->x + (WINDOW_WIDTH / 2 - player->x);
                game->bullets[i]->rect.y = game->bullets[i]->y + (WINDOW_HEIGHT / 2 - player->y);
                check_bullet(&game->bullets[i]);
                if (game->bullets[i] == NULL)
                    continue;
                // printf("blocat");
                for (int j = 0; j < COLONIES_COUNT * COLONY_POPULATION; ++j) {
                    if (game->food[j] != NULL && game->bullets[i] != NULL) {
                        int result = check_collision(game->bullets[i]->x, game->bullets[i]->y, BULLET_SIZE, BULLET_SIZE,
                                                    game->food[j]->x, game->food[j]->y, game->food[j]->rect.w, game->food[j]->rect.h);

                        if (result && game->bullets[i] != game->food[j]->last_hit) {
                            if (game->food[j]->dx <= 0.0001f)
                                game->food[j]->dx += (game->bullets[i]->dx / 2);
                            if (game->food[j]->dy <= 0.0001f)
                                game->food[j]->dy += (game->bullets[i]->dy / 2);
                            game->food[j]->health -= game->bullets[i]->power;

                            game->bullets[i]->penetration--;
                            if (game->bullets[i]->penetration == 0) {
                                free(game->bullets[i]);
                                game->bullets[i] = NULL;
                            }

                            game->food[j]->last_hit = game->bullets[i];
                            printf("HIT! New food health %d\n", game->food[j]->health);
                            if (game->food[j]->health <= 0) {
                                free(game->food[j]);
                                game->food[j] = NULL;
                                game->remaining_food--;
                            }

                        }
                    }
                }
            }
        }
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
    free_food(game->food);
    for (int i = 0; i < game->max_bullets; ++i) {
        if (game->bullets[i] != NULL)
            free(game->bullets[i]);
    }
    free(game->bullets);
    free(game);

    return 0;
}
