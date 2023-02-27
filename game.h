#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
#define FOOD_TYPES 3

#define DEFAULT_SPEED 3
#define ACCELERATION 0.1
#define SPEED_BONUS 0.25
#define BULLET_SPEED 3
#define DEFAULT_BULLET_TIME 2
#define TIME_BONUS 0.25
#define SHOOT_TIME_BONUS 0.075
#define DEFAULT_SHOOTING_SPEED 0.75
#define DEFAULT_BULLET_DAMAGE 50
#define BULLET_DAMAGE_BONUS 25
#define DEFAULT_BODY_DAMAGE 10
#define BODY_DAMAGE_BONUS 5

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
    clock_t creation;
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
    float dx;
    float dy;
    short health;
    short type;
    SDL_Rect rect;
    double rotation_angle;
    TBullet *last_hit;
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
    int power;
    int bullet_speed;
    int bullet_time;
    int bullet_penetration;
    int movement_speed;
    int body_damage;
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
    SDL_Texture* food_texture[FOOD_TYPES]; 
    SDL_Texture* body_texture;
    SDL_Texture* turret_texture;
    SDL_Texture* playground_texture;
    SDL_Texture* bullet_texture;
};

extern void check_bullet(TBullet**);
extern void default_shoot(TGameState*);
extern void free_bullets(TBullet*[], int);
extern TBullet* hit_bullet(TBullet*);

extern int check_collision (float, float, int, int, float, float, int, int);

extern void update_player_position(TTank*);
extern void update_turret_position(TTank*);
extern void update_bullet_position(TBullet*);
extern void update_playground_position(TGameState*, TTank*);

extern int handle_event(TGameState*);

extern void load_textures(TGameState*);
void connect_textures(TGameState*, TTank*);
extern void destroy_textures(TGameState*);
extern void render_game(TGameState*);

static TFood* alloc_food(short, int, int);
extern void free_food(TFood**, int);
extern void generate_new_colony(TGameState*);
