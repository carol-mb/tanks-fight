#pragma once
#include "game.h"
#include <SDL2/SDL.h>
#include <time.h>

#define FOOD_TRIANGLE 0
#define FOOD_SQUARE 1
#define FOOD_HEXAGON 2

#define TRIANGLES_COUNT 8
#define SQUARES_COUNT 3
#define HEXAGONS_COUNT 1

#define TRIANGLE_HEALTH 100
#define SQUARE_HEALTH 200
#define HEXAGON_HEALTH 500

#define SPREAD_RADIUS 256

static TFood* alloc_food(short, int, int);
extern void free_food(TFood**);
extern void generate_new_colony(TGameState*);
