#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <math.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define PLAYER_SIZE 64
#define TURRET_SIZE 32
#define BULLET_SIZE 16
#define PLAYGROUND_SIZE 1024

#define COLONY_POPULATION 12
#define COLONIES_COUNT 6

typedef struct Bullet TBullet;
typedef struct Turret TTurret;
typedef struct Body TBody;
typedef struct Tank TTank;
typedef struct Food TFood;
typedef struct GameState TGameState;

struct Bullet{
    float x;
    float y;
    float dx;
    float dy;
    int size;
    int power;
    int penetration;
    SDL_Rect rect;
    time_t creation;
    double duration;
};

struct Turret {
    int type;
    double rotation_angle;
    SDL_Rect rect;
};

struct Body {
    int type;
    int size;
    SDL_Rect rect;
};

struct Food {
    float x;
    float y;
    short health;
    short type;
    SDL_Rect rect;
    double rotation_angle;
};

struct Tank {
    TBody body;
    TTurret turret;
    int health;
    int level;
    int exp;
    float x;
    float y;
    float dx;
    float dy;
    int bullet_speed;
    int bullet_time;
    int movement_speed;
    double shooting_speed;
    clock_t last_shoot;
    void (*shooting_style)(TGameState*);
};

struct GameState {
    TTank *player;
    TFood *food[COLONIES_COUNT * COLONY_POPULATION];
    int remaining_food;
    
    TBullet **bullets;
    int max_bullets;

    SDL_Renderer *renderer;

    // rectangles
    SDL_Rect playground_rect;

    // textures
    SDL_Texture* food_texture[3]; 
    SDL_Texture* body_texture;
    SDL_Texture* turret_texture;
    SDL_Texture* playground_texture;
    SDL_Texture* bullet_texture;
};
