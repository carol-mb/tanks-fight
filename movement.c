#include "game.h"

void update_player_position(TTank *player) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    float max_speed = DEFAULT_SPEED + player->movement_speed * SPEED_BONUS;
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        if (player->dx > -1 * max_speed)
            player->dx -= ACCELERATION;
    }
    else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        if (player->dx < max_speed)
            player->dx += ACCELERATION;
    }
    else {
        player->dx *= 0.95f;
        if (fabs(player->dx) < 0.001f)
            player->dx = 0;
    }

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        if (player->dy > -1 * max_speed)
            player->dy -= ACCELERATION;
    }
    else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        if (player->dy < max_speed)
            player->dy += ACCELERATION;
    }
    else {
        player->dy *= 0.95f;
        if (fabs(player->dy) < 0.001f)
            player->dy = 0;
    }

    player->x += player->dx;
    player->y += player->dy;

    // right boundary
    if (player->x + PLAYER_SIZE > PLAYGROUND_SIZE)
        player->x = PLAYGROUND_SIZE - PLAYER_SIZE;

    // left boundary
    if (player->x < 0)
        player->x = 0;

    // bottom boundary
    if (player->y + PLAYER_SIZE > PLAYGROUND_SIZE)
        player->y = PLAYGROUND_SIZE - PLAYER_SIZE;

    // upper boundary
    if (player->y < 0)
        player->y = 0;

    player->body.rect.x = (WINDOW_WIDTH - player->body.rect.w) / 2;
    player->body.rect.y = (WINDOW_HEIGHT  - player->body.rect.h) / 2;
}

void update_turret_position(TTank *player) {
    int mouse_x;
    int mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    double slope = (mouse_y - WINDOW_HEIGHT / 2) * 1.0 / (mouse_x - WINDOW_WIDTH / 2); 
    // double rotation_angle = atan(slope);
    // double radians = rotation_angle * (M_PI / 180);
    double radians = atan(slope);
    double rotation_angle = radians * 180 / M_PI;
    player->turret.rotation_angle = rotation_angle;

    int side = 1;
    if (mouse_x < WINDOW_WIDTH / 2) {
        side = -1;
    }

    player->turret.rect.x = (WINDOW_WIDTH - player->turret.rect.w) / 2 + side * (player->body.rect.w / 2) * cos(radians);
    player->turret.rect.y = (WINDOW_HEIGHT - player->turret.rect.h) / 2 + side * (player->body.rect.h / 2) * sin(radians);
}

void update_bullet_position(TBullet *bullet) {
    bullet->x += bullet->dx;
    bullet->y += bullet->dy;
    bullet->rect.x = bullet->x;
    bullet->rect.y = bullet->y;
}

void update_playground_position(TGameState *game, TTank *player) {
    game->playground_rect.x = player->body.rect.x - player->x;
    game->playground_rect.y = player->body.rect.y - player->y;
}
