#include "food.h"

TFood* alloc_food(short type, int center_x, int center_y) {
    TFood *food = (TFood*)malloc(sizeof(TFood));
    switch (type) {
        case FOOD_TRIANGLE:
            food->type = FOOD_TRIANGLE;
            food->health = TRIANGLE_HEALTH;
        break;
        case FOOD_SQUARE:
            food->type = FOOD_SQUARE;
            food->health = SQUARE_HEALTH;
        break;
        case FOOD_HEXAGON:
            food->type = FOOD_HEXAGON;
            food->health = HEXAGON_HEALTH;
        break;
        default:
        break;
    }
    food->dx = 0;
    food->dy = 0;
    food->x = center_x + rand() % SPREAD_RADIUS;
    food->y = center_y + rand() % SPREAD_RADIUS;
    food->last_hit = NULL;

    food->rotation_angle = rand() % 360;

    return food;
}

void free_food(TFood *food[]) {
    for (int i = 0; i < COLONIES_COUNT * COLONY_POPULATION; ++i) {
        if (food[i] != NULL)
            free(food[i]);
    }
}

void generate_new_colony(TGameState *game) {
    int center_x = 0;
    int center_y = 0;
    int pos = 0;
    do {
        center_x = rand() % (PLAYGROUND_SIZE - SPREAD_RADIUS);
        center_y = rand() % (PLAYGROUND_SIZE - SPREAD_RADIUS);
    } while(abs(center_x - (int)game->player->x) < PLAYER_SIZE / 2 
            && abs(center_y - (int)game->player->x < PLAYER_SIZE) / 2);
    for (int i = 0; i < TRIANGLES_COUNT; ++i) {
        if (game->food[pos] == NULL) {
            game->food[pos] = alloc_food(FOOD_TRIANGLE, center_x, center_y);
            SDL_QueryTexture(game->food_texture[game->food[pos]->type], NULL, NULL, &game->food[pos]->rect.w, &game->food[pos]->rect.h);
        }
        else {
            ++pos;
            --i;
        }
    }

    for (int i = 0; i < SQUARES_COUNT; ++i) {
        if (game->food[pos] == NULL) {
            game->food[pos] = alloc_food(FOOD_SQUARE, center_x, center_y);
            SDL_QueryTexture(game->food_texture[game->food[pos]->type], NULL, NULL, &game->food[pos]->rect.w, &game->food[pos]->rect.h);
        }
        else {
            ++pos;
            --i;
        }
    }

    for (int i = 0; i < HEXAGONS_COUNT; ++i) {
        if (game->food[pos] == NULL) {
            game->food[pos] = alloc_food(FOOD_HEXAGON, center_x, center_y);
            SDL_QueryTexture(game->food_texture[game->food[pos]->type], NULL, NULL, &game->food[pos]->rect.w, &game->food[pos]->rect.h);
        }
        else {
            ++pos;
            --i;
        }
    }

    game->remaining_food += COLONY_POPULATION;
}
