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

    menu();
    select();

    //pause();
    system("pause");
    return 0;
}
void select(){
    int sign = 0;
    scanf("%d", &sign);
    printf("\n");
    switch (sign) {
        case 1:
            run_calculate();
            break;
        case 2:
            run_translations();
            break;
        case 3:
            run_greedy_snake();
            break;
    }
}
void menu(){
    printf("1.四则运算生成器\n");
    printf("2.翻译器\n");
    printf("3.贪吃蛇\n");
    printf("请选择序号:");
}
