#include "game.h"

int check_collision (float obj_x, float obj_y, int obj_width, int obj_height,
                    float block_x, float block_y, int block_width, int block_height) {
    
    // right and left
    if (obj_x + obj_width / 2 >= block_x - block_width / 2
        && obj_x + obj_width / 2 <= block_x + block_width / 2
        && obj_y <= block_y + block_height / 2
        && obj_y >= block_y - block_height / 2)
        return 1;

    if (obj_x - obj_width / 2 >= block_x - block_width / 2
        && obj_x - obj_width / 2 <= block_x + block_width / 2
        && obj_y <= block_y + block_height / 2
        && obj_y >= block_y - block_height / 2)
        return 2;

    // above and below
    if (obj_x >= block_x - block_width / 2
        && obj_x <= block_x + block_width / 2
        && obj_y + obj_height / 2 <= block_y + block_height / 2
        && obj_y + obj_height / 2 >= block_y - block_height / 2)
        return 3;

    if (obj_x >= block_x - block_width / 2
        && obj_x <= block_x + block_width / 2
        && obj_y - obj_height / 2 <= block_y + block_height / 2
        && obj_y - obj_height / 2 >= block_y - block_height / 2)
        return 4;

    return 0;
}
