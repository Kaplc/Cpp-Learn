//
// Created by Kapl on 2023/4/22.
//
#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "../header/greedy_snake.h"


#define MAP_X 100
#define MAP_Y 25


typedef struct body {
    int body_x;
    int body_y;
} BODY;

typedef struct snake {
    int heard_x;
    int heard_y;
    int food_x;
    int food_y;
    BODY *body;
    int body_count;
} SNAKE;

void add_body(SNAKE *snake) {
    snake->body_count++;
    snake->body = (BODY *) calloc(snake->body_count, sizeof(BODY));
    for (int body_num = 0; body_num < MAP_X * MAP_Y; ++body_num) {

    }
}

void print_snake(int x, int y, char symbol) {
    /*打印蛇和食物*/
    // <windows.h>设置光标位置
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", symbol);
    fflush(stdout);

}

void generate_food(SNAKE *snake) {
    /*随机生成食物*/
    do {
        srand(time(NULL) + 1);
        snake->food_x = rand() % MAP_X + 1;
        snake->food_y = (rand() % MAP_Y) + 1;
    } while (!(snake->food_x <= MAP_X - 3 && snake->food_y <= MAP_Y - 3)); // 判断生成在地图内

}

void init_snake() {
    /*初始化蛇*/
    SNAKE snake;
    // 头部
    snake.heard_x = (MAP_X - 2) / 2;
    snake.heard_y = (MAP_Y - 2) / 2;
    // 初始化一节身体
    snake.body_count = 1;
//    add_body(&snake);
    snake.body = (BODY *) calloc(1, sizeof(BODY));
    snake.body->body_x = snake.heard_x - 1;
    snake.body->body_y = snake.heard_y;

    generate_food(&snake);// 生成食物
    // 打印
    print_snake(snake.heard_x, snake.heard_y, '@'); // '@'打印头
    print_snake(snake.food_x, snake.food_y, '$');
    print_snake(snake.body->body_x, snake.body->body_y, 'o');

}

void generate_map() {
    /*
     * 生成地图
     * (可活动范围MAP_X-2 MAP_Y-2)
     * */
    for (int wall_y = 0; wall_y < MAP_Y; ++wall_y) {

        for (int wall_x = 0; wall_x < MAP_X; ++wall_x) {
            // 四角生成'+'
            if ((wall_y == 0 && wall_x == 0) || (wall_y == 0 && wall_x == MAP_X - 1) ||
                (wall_y == MAP_Y - 1 && wall_x == 0) || (wall_y == MAP_Y - 1 && wall_x == MAP_X - 1)) {
                printf("+");
                fflush(stdout);
            }
            if ((wall_x >= 1 && wall_x < MAP_X - 1) && (wall_y == 0 || wall_y == MAP_Y - 1)) { // 上下墙
                printf("-");
                fflush(stdout);
            } else if ((wall_y >= 1 && wall_y < MAP_Y - 1) && (wall_x == 0 || wall_x == MAP_X - 1)) { // 左右墙
                printf("|");
                fflush(stdout);
            } else if ((wall_y >= 1 && wall_y < MAP_Y - 1) && (wall_x >= 1 && wall_x <= MAP_X - 1)) { // 中间空格
                printf(" ");
                fflush(stdout);
            }
        }
        printf("\n");


    }
}

void init_game() {
    /*初始化游戏*/
    generate_map(); // 生成地图
    init_snake(); // 初始化蛇
}

void run_greedy_snake() {
    init_game(); // 初始化游戏
}