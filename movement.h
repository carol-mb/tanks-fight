#pragma once
#include "game.h"
#include <SDL2/SDL.h>
#include <math.h>

#define DEFAULT_SPEED 3
#define ACCELERATION 0.1
#define SPEED_BONUS 0.25
#define BULLET_SPEED 3
#define DEFAULT_BULLET_TIME 3
#define TIME_BONUS 0.25
#define SHOOT_TIME_BONUS 0.075
#define DEFAULT_SHOOTING_SPEED 0.75

extern void update_player_position(TTank*);
extern void update_turret_position(TTank*);
extern void update_bullet_position(TBullet*);
