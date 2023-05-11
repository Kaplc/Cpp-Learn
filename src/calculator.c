//
// Created by kaplc on 2023/5/8.
//

#include "../header/calculator.h"
#include "../header/cal_stack.h"
#include "../header/cal_link.h"
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

LINKLIST *convert_suffix(char expression[]) {
    // 初始化储存后缀式链表
    LINKLIST *linklist = init_calLink();
    // 初始化符号栈
    STACK *signStack = init_calstack();;
    char *pExp = expression;

    for (int i = 0; i < strlen(expression) - 1; ++i) {
        // 当前字符地址
        char *currChar = pExp + i;

        if (*currChar >= '0' && *currChar <= '9') { // 数字直接输出
            // 保存整个数字
            double *num = malloc(sizeof(double));
            sscanf(currChar, "%lf", num);
            printf("%.1lf", *num);
            fflush(stdout);
            // 生成节点‘n’标识为数字
            NODE *node = generate_node(num, 'n');
            // 节点添加进后缀式链表，
            add_node(linklist, node);
            // 跳过整个数字长度，将指针移动到下个字符
            for (int move = i; *(pExp + move) >= '0' && *(pExp + move) <= '9' || *(pExp + move) == '.'; ++move) {
                i = move;
            }

        } else {
            // 符号生成节点‘s’标识为符号
            NODE *curr_node = generate_node(pExp + i, 's');

            if (signStack->size == 0) { // 符号栈为空直接入栈
                push_calstack(signStack, curr_node); // 压入符号栈
                continue;
            }

            // 生成优先级标识
            char *res = (char *) read_calstack_top(signStack)->data; // 出栈返回的是节点
            int stackPriority = -1;
            int currPriority = -1;
            stackPriority = judge_priority(*res);
            currPriority = judge_priority(*currChar);

            // 优先级判断
            if (*(pExp + i) == ')') { // 遇到右括号
                while (*((char *) read_calstack_top(signStack)->data) != '(') { // 符号栈一直出栈并添加进链表直到左括号
                    NODE *pop_node = pop_calstack(signStack);
                    printf("%c", *(char *) pop_node->data);
                    fflush(stdout);
                    // 节点添加进后缀式链表，
                    add_node(linklist, pop_node);
                }
                free(pop_calstack(signStack)); // 出掉')'并丢弃

            } else if (*(pExp + i) == '(' || currPriority >= stackPriority) { // 左括号直接入栈，入栈后优先级最低 或者 优先级大于也直接入栈
                push_calstack(signStack, curr_node);

            } else { // 当前字符优先级小于栈顶
                // 源栈顶先出栈， 添加进后缀链表
                NODE *pop_node = pop_calstack(signStack);
                printf("%c", *(char *) pop_node->data);
                fflush(stdout);
                add_node(linklist, pop_node);

                // 当前字符入栈
                push_calstack(signStack, curr_node);
            }
        }

    }

    for (int i = signStack->size; i > 0; --i) {
        char sign = *(char *) pop_calstack(signStack)->data;
        printf("%c", sign);
        fflush(stdout);
    }

}

void operation() {

}

void run_calculator() {
    char expression[1024] = {0};
    fgets(expression, 1024, stdin);


    char resSuffix[1024] = {0};
    convert_suffix(expression);
}