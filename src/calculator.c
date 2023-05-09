//
// Created by kaplc on 2023/5/8.
//

#include "../header/calculator.h"
#include "../header/stack.h"
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

void convert_suffix(char expression[], char resSuffix[], STACK *expStack) {
    char *pExp = expression;
    for (int i = 0; i < strlen(expression) - 1; ++i) {
        if (*(pExp + i) >= '0' && *(pExp + i) <= '9') { // 数字直接输出
            printf("%c", *(pExp + i));
            fflush(stdout);
//            *resSuffix = *pExp;
        } else {
            if (expStack->size == 0) { // 栈为空直接入栈
                push_stack(expStack, pExp + i);
                continue;
            }
            int stackPriority = -1;
            int currPriority = -1;
            char *res = read_stack_top(expStack);
            // 生成优先级标识
            stackPriority = judge_priority(*res);
            currPriority = judge_priority(*(pExp + i));

            // 优先级判断
            if (*(pExp + i) == ')') { // 遇到右括号
                while (*(char *) read_stack_top(expStack) != '(') {
                    printf("%c", *(char *) pop_stack(expStack));
                    fflush(stdout);
                }
                pop_stack(expStack); // 出掉')'

            } else if (*(pExp + i) == '(') { // 左括号直接入栈，入栈后优先级最低
                push_stack(expStack, pExp + i);

            } else if (currPriority >= stackPriority) { // 当前字符优先级大于栈顶
                push_stack(expStack, pExp + i);

            } else { // 当前字符优先级小于栈顶
                printf("%c", *(char *) pop_stack(expStack)); // 源栈顶先出栈
                push_stack(expStack, pExp + i); // 当前字符入栈

            }

        }

    }

    for (int i = expStack->size; i > 0; --i) {
        printf("%c", *(char *) pop_stack(expStack));
        fflush(stdout);
    }
}

void operation() {

}

void run_calculator() {
    char expression[1024] = {0};
    fgets(expression, 1024, stdin);

    STACK *expStack = NULL;
    expStack = init_stack();
    char resSuffix[1024] = {0};
    convert_suffix(expression, resSuffix, expStack);
}