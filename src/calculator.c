//
// Created by kaplc on 2023/5/8.
//

#include "../header/calculator.h"
#include "../header/cal_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int judge_priority(char sign) {
    int resPriority = -1;
    switch (sign) {
        case '+':
        case '-':
            resPriority = 1;
            break;
        case '*':
        case '/':
            resPriority = 2;
            break;
        case '(':
            resPriority = 0;
            break;
        case ')':
            break;
        default:
            printf("输入符号错误");
            break;
    }
    return resPriority;
}

void convert_suffix(char expression[], STACK *signStack) {
    STACK *numStack = init_calstack();
    char *pExp = expression;

    for (int i = 0; i < strlen(expression) - 1; ++i) {
        if (*(pExp + i) >= '0' && *(pExp + i) <= '9') { // 数字直接输出
            double *num = malloc(sizeof(double ));
//            int num = 0;
            sscanf(pExp + i, "%lf", num);
            printf("%.1lf", *num);
            fflush(stdout);
            push_calstack(numStack, num, 'n'); // 压入计算栈，‘n’标识为数字

            for (int move = i; *(pExp + move) >= '0' && *(pExp + move) <= '9' || *(pExp + move)=='.'; ++move) {
                i = move;
            }

        } else {
            if (signStack->size == 0) { // 栈为空直接入栈
                push_calstack(signStack, pExp + i, 's'); // 压入符号栈
                continue;
            }
            int stackPriority = -1;
            int currPriority = -1;
            char *res = (char *)read_calstack_top(signStack)->data; // 出栈返回的是节点
            // 生成优先级标识
            stackPriority = judge_priority(*res);
            currPriority = judge_priority(*(pExp + i));

            // 优先级判断
            if (*(pExp + i) == ')') { // 遇到右括号
                while (*(char *) read_calstack_top(signStack) != '(') { // 符号栈一直出栈直到左括号
                    printf("%c", *(char *)pop_calstack(signStack)->data);
                    fflush(stdout);
                    push_calstack(numStack, pop_calstack(signStack)->data, 's'); // 出来的符号压入计算栈
                }
                pop_calstack(signStack); // 出掉')'并丢弃

            } else if (*(pExp + i) == '(') { // 左括号直接入栈，入栈后优先级最低
                push_calstack(signStack, pExp + i, 's');

            } else if (currPriority >= stackPriority) { // 当前字符优先级大于栈顶
                push_calstack(signStack, pExp + i, 's');

            } else { // 当前字符优先级小于栈顶
                // 源栈顶先出栈
                printf("%c", *(char *) read_calstack_top(signStack));
                push_calstack(numStack, pop_calstack(signStack)->data, 's');
                // 当前字符入栈
                push_calstack(signStack, pExp + i, 's');
            }
        }

    }

    for (int i = signStack->size; i > 0; --i) {
        char sign = *(char *) pop_calstack(signStack);
        printf("%c", sign);
        fflush(stdout);
    }
    read_calstack(numStack);
}

void operation() {

}

void run_calculator() {
    char expression[1024] = {0};
    fgets(expression, 1024, stdin);

    STACK *signStack = NULL;
    signStack = init_calstack();
    char resSuffix[1024] = {0};
    convert_suffix(expression, signStack);
}