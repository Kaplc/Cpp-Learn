//
// Created by Kapl on 2023/4/22.
//
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#include "../header/greedy_snake.h"


#define MAP_X 60
#define MAP_Y 25
#define SPEED 6

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

    int score;

} SNAKE;

void print_snake(SNAKE *snake);


void add_body(SNAKE *snake) {
    snake->body_count++;
    snake->body = (BODY *) calloc(snake->body_count, sizeof(BODY));
    for (int body_num = 0; body_num < MAP_X * MAP_Y; ++body_num) {

    }
}

int cal_score(SNAKE *snake) {
    /*计算分数*/
    snake->score += snake->body_count;
}

int collision_judgment(SNAKE *snake) {
    /*墙碰撞判断*/
    if (snake->body->body_x == 0 || snake->body->body_x == MAP_X - 1 || snake->body->body_y == 0 ||
        snake->body->body_y == MAP_Y - 1) {
        return 1;
    }
    return 0;
}

void read_keyboard(SNAKE *snake) {
    char key;
    while (_kbhit()) //判断是否按下按键,按下不等于0
    {
        key = _getch();
//        key = 'a';
        switch (key) {
            case 'w':
                if (snake->dx == 0 && snake->dy == 1)break; // 与行驶方向相反不进行操作
                snake->dx = 0;
                snake->dy = -1;
                break;
            case 's':
                if (snake->dx == 0 && snake->dy == -1)break;
                snake->dx = 0;
                snake->dy = 1;
                break;
            case 'a':
                if (snake->dx == 1 && snake->dy == 0)break;
                snake->dx = -1;
                snake->dy = 0;
                break;
            case 'd':
                if (snake->dx == -1 && snake->dy == 0)break;
                snake->dx = 1;
                snake->dy = 0;
                break;
        }
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
        read_keyboard(snake);

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

        if (collision_judgment(snake)) {
            break;
        }
        print_snake(snake);

        usleep(1000000 / SPEED); // 休眠250毫秒, 单位微秒

    }

}

void print_snake(SNAKE *snake) {
    /*打印蛇和食物*/
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

    coord.X = snake->food_x;
    coord.Y = snake->food_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", '$');

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

void init_snake(SNAKE **ppsnake) {
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
    // 打印蛇和食物
    print_snake(snake);
    // 初始化分数
    snake->score = 0;
    *ppsnake = snake;
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

void init_game(SNAKE **ppsnake) {
    /*初始化游戏*/
    generate_map(); // 生成地图
    init_snake(ppsnake); // 初始化蛇

}

void run_greedy_snake() {
    SNAKE *snake = NULL;

    init_game(&snake); // 初始化游戏
    snake_moving(snake); // 开始游戏
    cal_score(snake); // 计算分数
    COORD coord;
    coord.X = MAP_X / 2 - 7;
    coord.Y = MAP_Y + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("游戏结束 分数:%d", snake->score);

}