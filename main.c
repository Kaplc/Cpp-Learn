#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "header/calculate.h"
#include "header/utility.h"
#include "header/translation.h"
#include "header/greedy_snake.h"

void menu();

void select();

//程序入口
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

//    run_calculate(); // 四则运算生成器
//    run_translations(); // 快译通翻译
    run_greedy_snake(); // 贪吃蛇


    printf("\n");
    //pause();
//    system("pause");
    getchar();
    return 0;
}

