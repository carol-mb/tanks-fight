#pragma once
#include "game.h"
#include <SDL2/SDL.h>
#include <math.h>

#define DEFAULT_SPEED 3
#define ACCELERATION 0.1
#define SPEED_BONUS 0.25

extern void update_player_position(TTank*);
extern void update_turret_position(TTank*);
