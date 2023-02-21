#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <math.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define PLAYER_SIZE 64
#define TURRET_SIZE 32
#define PLAYGROUND_SIZE 1024

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
    int size;
    int power;
    int penetration;
} TBullet;

typedef struct {
    int type;
    double rotation_angle;
    SDL_Rect rect;
} TTurret;

typedef struct {
    int type;
    int size;
    SDL_Rect rect;
} TBody;

typedef struct {
    TBody body;
    TTurret turret;
    int health;
    int level;
    int exp;
    float x;
    float y;
    float dx;
    float dy;
    int shooting_speed;
    int movement_speed;
    TBullet** bullets;
    TBullet* (*shooting_style)();
} TTank;


typedef struct {
    int health;
    float x;
    float y;
    int width;
    int height;
} TFood;

typedef struct {
    TTank *player;
    SDL_Renderer *renderer;

    // rectangles
    SDL_Rect playground_rect;

    // textures
    SDL_Texture* food_textures[3]; 
    SDL_Texture* body_texture;
    SDL_Texture* turret_texture;
    SDL_Texture* playground_texture;
} TGameState;
