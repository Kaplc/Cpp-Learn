//
// Created by Kapl on 2023/4/22.
//
#include <stdio.h>

#include "../header/greedy_snake.h"

#define MAP_X 100
#define MAP_Y 20

typedef struct snake {
    int heard_x;
    int heard_y;
} SNAKE;

void init_snake() {

}

void generate_map() {
    for (int wall_y = 0; wall_y < MAP_Y ; ++wall_y) {

        for (int wall_x = 0; wall_x < MAP_X ; ++wall_x) {
            // 四角生成'+'
            if ((wall_y == 0 && wall_x == 0) || (wall_y == 0 && wall_x == MAP_X -1) ||
                (wall_y == MAP_Y -1 && wall_x == 0) || (wall_y == MAP_Y -1 && wall_x == MAP_X - 1)) {
                printf("+");
                fflush(stdout);
            }
            if ((wall_x >= 1 && wall_x < MAP_X - 1) && (wall_y == 0 || wall_y == MAP_Y - 1)) { // 上下墙
                printf("-");
                fflush(stdout);
            } else if ((wall_y >= 1 && wall_y < MAP_Y - 1) && (wall_x == 0 || wall_x == MAP_X - 1)) { // 左右墙
                printf("|");
                fflush(stdout);
            } else if ((wall_y >= 1 && wall_y < MAP_Y - 1) && (wall_x >= 1 && wall_x <= MAP_X - 1)){ // 中间空格
                printf(" ");
                fflush(stdout);
            }
        }
        printf("\n");


    }
}

void init_game() {
    generate_map();
    init_snake();
}

void run_greedy_snake() {
    init_game();
}