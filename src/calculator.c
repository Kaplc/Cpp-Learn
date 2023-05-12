//
// Created by kaplc on 2023/5/8.
//

#include "../header/calculator.h"
#include "../header/cal_stack.h"
#include "../header/cal_link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int judge_expression(char expression[]) {
    char *curr_char = expression;
    char *first_char = expression;
    int num_count = 0;
    int sign_count = 0;
    int rightParenthesis_count = 0;
    int leftParenthesis_count = 0;
    int leng = strlen(expression);
    for (int i = 0; i < strlen(expression)-1; ++i) {
        curr_char = first_char + i;
        if (*curr_char >= '0' && *curr_char <= '9') {
            // 记录数字个数
            for (int move = i; *(first_char + move) >= '0' && *(first_char + move) <= '9' || *(first_char + move) == '.'; ++move) {
                i = move;
            }
            num_count++;
        } else if (*curr_char == '+' || *curr_char == '-' || *curr_char == '*' || *curr_char == '/') {
            // 记录运算符个数
            sign_count++;
        } else if (*curr_char == '(') {
            // 记录左括号个数
            leftParenthesis_count++;
        } else if (*curr_char == ')') {
            // 记录右括号个数
            rightParenthesis_count++;
        } else {
            return 0;
        }
    }
    return num_count == (sign_count + 1) && leftParenthesis_count == rightParenthesis_count ? EXPRESSION_ISRTUE
                                                                                            : EXPRESSION_ISFALSE;

}
// 3.5*2+(7-2)-1
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

double *start_cal(double right, double left, char sign) {
    double *res = malloc(sizeof(double));
    switch (sign) {
        case '+':
            *res = left + right;
            break;
        case '-':
            *res = left - right;
            break;
        case '*':
            *res = left * right;
            break;
        case '/':
            if (right == 0) {
                return NULL;
                break;
            }
            *res = left / right;

            break;
    }
    return res;
}

LINKLIST *convert_suffix(char expression[]) {
    // 判断表达式合法性
    if (judge_expression(expression) == 0) {
        return NULL;
    }

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
//            printf("%.1lf", *num);
            fflush(stdout);
            // 生成节点‘n’标识为数字
            NODE *node = generate_node(num, 'n');
            // 节点添加进后缀式链表，
            add_node(linklist, node);
            // 跳过整个数字长度，将指针移动到下个字符
            for (int move = i; *(pExp + move) >= '0' && *(pExp + move) <= '9' || *(pExp + move) == '.'; ++move) {
                i = move;
            }

        } else if (*currChar == '+' || *currChar == '-' || *currChar == '*' || *currChar == '/' || *currChar == '(' ||
                   *currChar == ')') {

            // 符号生成节点‘s’标识为符号
            NODE *curr_node = generate_node(currChar, 's');

            if (signStack->size == 0) { // 符号栈为空直接入栈
                push_calstack(signStack, curr_node); // 压入符号栈
                continue;
            }

            // 生成优先级标识
            char *top_sign = (char *) read_calstack_top(signStack)->data; // 出栈返回的是节点
            int stackPriority = -1;
            int currPriority = -1;
            stackPriority = judge_priority(*top_sign);
            currPriority = judge_priority(*currChar);

            // 优先级判断
            if (*(pExp + i) == ')') { // 遇到右括号
                while (*((char *) read_calstack_top(signStack)->data) != '(') { // 符号栈一直出栈并添加进链表直到左括号
                    NODE *pop_node = pop_calstack(signStack);
//                    printf("%c", *(char *) pop_node->data);
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
//                printf("%c", *(char *) pop_node->data);
                fflush(stdout);
                add_node(linklist, pop_node);

                // 当前字符入栈
                push_calstack(signStack, curr_node);
            }
        } else {

            return NULL;
        }
    }

    for (int i = signStack->size; i > 0; --i) {
        NODE *pop_node = pop_calstack(signStack);
        add_node(linklist, pop_node);
        char sign = *(char *) pop_node->data;
//        printf("%c", sign);
        fflush(stdout);
    }

    return linklist;
}

double *use_suffix_cal(LINKLIST *linklist) {
    // 初始化计算栈
    STACK *cal_stack = init_calstack();
    NODE *current_node = &(linklist->header);

    while (current_node->next != NULL) {
        current_node = current_node->next;
        NODE *res_node = malloc(sizeof(NODE));
        if (current_node->type == 'n') { // 数字直接入栈
            res_node->next = NULL;
            res_node->data = current_node->data;
            res_node->type = current_node->type;
            push_calstack(cal_stack, res_node);
        } else if (current_node->type == 's') { // 遇到符号
            // 右操作数出栈
            double right_num = *(double *) pop_calstack(cal_stack)->data;
            // 左操作数出栈
            double left_num = *(double *) pop_calstack(cal_stack)->data;
            // 进行计算后结果入栈
            double *res = malloc(sizeof(double));
            res = start_cal(right_num, left_num, *(char *) current_node->data);
            if (res == NULL) {

                return NULL;
            }
            res_node->next = NULL;
            res_node->data = res;
            res_node->type = 'n';
            push_calstack(cal_stack, res_node);
        }
    }
    double *finally_res = malloc(sizeof(double));
    finally_res = (double *) cal_stack->header.next->data;
    return finally_res;
}

void run_calculator() {
    printf("请输入表达式(例：3.5*2+(7-2)-1)：\n");
    while (1) {
        char expression[1024] = {0};
        fgets(expression, 1024, stdin);

        LINKLIST *suffix_linklist = convert_suffix(expression);
        if (suffix_linklist == NULL) {
            printf("表达式错误！\n");
            continue;
        }
        double *res = use_suffix_cal(suffix_linklist);
        if (res == NULL) {
            printf("除数不能为0!\n");
            continue;
        }
        int int_part = (int) *res;
        double decimal_part = int_part - *res;
        if (decimal_part == 0.0000) {
            printf("%d", int_part);
        } else {
            printf("%.3lf", *res);
        }
        printf("\n");
    }
}