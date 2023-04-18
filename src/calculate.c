#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../header/utility.h"

void generator_data_to_write(int count) {

    int rand_num = 0, num1 = 0, num2 = 0;
    int sign_num = 0;
    char sign[] = {'+', '-', '*', '/'};
    char buf[1024] = {0};
    char signn = 0;
    FILE *fp = NULL;

    for (int i = 0, len = 0; i < count; i++) {
        //生成随机数
        srand(time(NULL) + i);
        rand_num = rand();

        // +1保证非零
        num1 = rand_num % 100 + 1;
        num2 = ((rand_num % 10000) / 100) + 1;

        sprintf(buf + len, "%d%c%d=\n", num1, sign[rand_num % 4], num2); // 组包
        len = strlen(buf);
    }

    fp = fopen("../temp_file/calculate.txt", "w"); // 打开文件
    if (!fp)return; // 判断是否成功打开
    fputs(buf, fp); // 写入
    fclose(fp); // 关闭文件
    printf("文件生成成功\n");
}

void read_to_calculate() {
    int num1 = 0, num2 = 0;
    char sign = 0;
    char buf[10240] = {0};
    double res = 0;

    FILE *fp = NULL;

    fp = fopen("../temp_file/calculate.txt", "r+"); // 打开文件
    if (!fp)return;

    for (int len = 0; !feof(fp);) {
        fscanf(fp, "%d%c%d=\n", &num1, &sign, &num2); // 读文件拆包
        switch (sign) {
            case '+':
                res = num1 + num2;
                break;
            case '-':
                res = num1 - num2;
                break;
            case '*':
                res = num1 * num2;
                break;
            case '/':
                res = (double)num1 / num2;
                break;
        }
        sprintf(buf + len, "%d%c%d=%.2lf\n", num1, sign, num2, res); // 组包
        len = strlen(buf);
    }
    rewind(fp); // 光标移动到开头
    fputs(buf, fp);
    fclose(fp);
    printf("计算完成\n");
}

void run_calculate() {
    int count = 0;
    printf("请输入生成表达式数目:");
    scanf("%d", &count);
    generator_data_to_write(count);
    read_to_calculate();
}
