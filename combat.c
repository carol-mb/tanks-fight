#include "combat.h"
#include "movement.h"

void check_bullet(TBullet **bullet) {
    clock_t stop = clock();
    if ((double)(stop - (*bullet)->creation) / CLOCKS_PER_SEC * 25 >= (*bullet)->duration) {
        free(*bullet);
        *bullet = NULL;
    }
}

void default_shoot(TGameState *game) {
    int done = 0;
    int pos = 0;
    for (int i = 0; i < game->max_bullets; ++i) {
        if(game->bullets[i] == NULL) {
            pos = i;
            done = 1;
            break;
        }
    }
    if (!done) {
        printf("mareste, %d %d\n", game->max_bullets, game->max_bullets * 2);
        game->bullets = (TBullet**)realloc(game->bullets, sizeof(TBullet*) * game->max_bullets * 2);
        for (int i = game->max_bullets; i < game->max_bullets * 2; ++i)
            game->bullets[i] = NULL;
        pos = game->max_bullets;
        game->max_bullets *= 2;
        printf("a marit, %d\n", game->max_bullets);
    }
    game->bullets[pos] = (TBullet*)malloc(sizeof(TBullet));
    game->bullets[pos]->rect.w = 16;
    game->bullets[pos]->rect.h = 16;
    game->bullets[pos]->x = game->player->x - (game->player->body.rect.x - game->player->turret.rect.x) - TURRET_SIZE / 2 - BULLET_SIZE / 2;
    game->bullets[pos]->y = game->player->y - (game->player->body.rect.y - game->player->turret.rect.y) - TURRET_SIZE / 2 - BULLET_SIZE / 2;
    game->bullets[pos]->penetration = 1 + game->player->bullet_penetration;
    game->bullets[pos]->power = DEFAULT_BULLET_DAMAGE + game->player->power * BULLET_DAMAGE_BONUS;

    game->bullets[pos]->creation = clock();
    game->bullets[pos]->duration = DEFAULT_BULLET_TIME + game->player->bullet_time * TIME_BONUS;

    int mouse_x;
    int mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    double slope = (mouse_y - WINDOW_HEIGHT / 2) * 1.0 / (mouse_x - WINDOW_WIDTH / 2); 
    // double rotation_angle = atan(slope);
    // double radians = rotation_angle * (M_PI / 180);
    double radians = atan(slope);

    int side = 1;
    if (mouse_x < WINDOW_WIDTH / 2) {
        side = -1;
    }

    game->bullets[pos]->dx = side * (BULLET_SPEED + game->player->bullet_speed * SPEED_BONUS) * cos(radians);
    game->bullets[pos]->dy = side * (BULLET_SPEED + game->player->bullet_speed * SPEED_BONUS) * sin(radians);
    game->player->last_shoot = clock();
}
