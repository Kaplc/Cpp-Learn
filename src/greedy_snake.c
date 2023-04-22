//
// Created by Kapl on 2023/4/22.
//
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

#include "../header/greedy_snake.h"


#define MAP_X 100
#define MAP_Y 25
#define SPEED 10

typedef struct body {
    int body_x;
    int body_y;
} BODY;

typedef struct snake {

    int food_x;
    int food_y;

    int body_count;
    BODY *body;

    // 方向
    int dx;
    int dy;

} SNAKE;

void print_snake(SNAKE *snake);

void add_body(SNAKE *snake) {
    snake->body_count++;
    snake->body = (BODY *) calloc(snake->body_count, sizeof(BODY));
    for (int body_num = 0; body_num < MAP_X * MAP_Y; ++body_num) {

    }
}

void cls_tail(SNAKE *snake) {
    /*移动前清除尾部*/
    // 取尾部坐标
    int tail_x = 0;
    int tail_y = 0;

    tail_x = ((snake->body) + ((snake->body_count) - 1))->body_x;
    tail_y = ((snake->body) + ((snake->body_count) - 1))->body_y;

    COORD coord;
    coord.X = tail_x;
    coord.Y = tail_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", ' ');
    fflush(stdout);


}

void snake_moving(SNAKE *snake) {
    /*更新头和身体的坐标*/

    while (TRUE) {
        cls_tail(snake);
        // 更新身体坐标
        for (int i = (snake->body_count - 1); i > 0; i--) {
            // 头自主更新, 3=2 2=1 1=0
            ((snake->body) + i)->body_x = ((snake->body) + (i - 1))->body_x;
            ((snake->body) + i)->body_y = ((snake->body) + (i - 1))->body_y;

        }
        // 更新头部坐标
        (snake->body)->body_x += snake->dx;
        (snake->body)->body_y += snake->dy;

        print_snake(snake);

        usleep(1000000 / SPEED); // 休眠250毫秒, 单位微秒

    }

}

void print_snake(SNAKE *snake) {
    /*打印蛇*/
    // <windows.h>设置光标位置
    COORD coord;
//    system("cls");
    for (int i = 0; i < snake->body_count; ++i) {
        coord.X = ((snake->body) + i)->body_x;
        coord.Y = ((snake->body) + i)->body_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (i == 0) {
            printf("%c", '@');
            fflush(stdout);
        } else {
            printf("%c", 'o');
            fflush(stdout);
        }
    }


}

void print_food(int x, int y, char symbol) {
    /*打印食物*/
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
    } while (!(snake->food_x >= 2 && snake->food_x <= MAP_X - 3 && snake->food_y >= 2 &&
               snake->food_y <= MAP_Y - 3)); // 判断生成在地图内

}

SNAKE *init_snake() {
    /*初始化蛇*/
    SNAKE *snake = (SNAKE *) calloc(1, sizeof(SNAKE));
    // 初始化头部和两节身体
    snake->body_count = 3;
    snake->body = (BODY *) calloc(snake->body_count, sizeof(BODY));
    for (int i = 0; i < 3; ++i) {
        ((snake->body) + i)->body_x = ((MAP_X - 2) / 2) - i;
        ((snake->body) + i)->body_y = (MAP_Y - 2) / 2;
    }
    // 初始化方向
    snake->dx = 1;
    snake->dy = 0;
    // 生成食物
    generate_food(snake);
    // 打印
    print_food(snake->food_x, snake->food_y, '$'); //打印食物
    print_snake(snake);

    return snake;
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

SNAKE *init_game() {
    /*初始化游戏*/
    SNAKE *snake;
    generate_map(); // 生成地图
    snake = init_snake(); // 初始化蛇
    return snake;
}

void run_greedy_snake() {
    SNAKE *snake;
    snake = init_game(); // 初始化游戏
    snake_moving(snake);
}