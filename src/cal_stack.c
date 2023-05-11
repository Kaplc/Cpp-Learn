//
// Created by kaplc on 2023/5/7.
//

#include <stdlib.h>
#include <stdio.h>
#include "../header/cal_stack.h"


STACK *init_calstack() {
    // 初始化栈

    STACK *stack = malloc(sizeof(struct stack));
    stack->size = 0;
    stack->header.next = NULL;
    stack->header.type = 'h';
    return stack;
}

NODE *generate_node(void *data, char type){
    // 初始化新节点
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = NULL;
    new_node->type = type; // 标识类型

    return new_node;
}

void push_calstack(STACK *stack, NODE* node) {
    if (stack == NULL || node == NULL)return;

    // 连接入栈
    NODE *current = &(stack->header);
    node->next = current->next;
    current->next = node;
    stack->size++;

}

NODE * pop_calstack(STACK *stack) {
    if (stack == NULL || stack->size <= 0)return NULL;

    NODE *current = &(stack->header);
    // 从头节点指向第一个节点
    current = current->next;
//    printf("%d\n", *((int *) (current->data)));
    // 头结点指向第二个节点
    stack->header.next = current->next;
    stack->size--;

    return current;
}

NODE * read_calstack_top(STACK *stack) {
    if (stack == NULL || stack->size <= 0)return NULL;
    return stack->header.next;
}

void read_calstack(STACK *stack) {
    if (stack == NULL)return;

    int total_size = stack->size;
    for (int i = 0; i < total_size; ++i) {
        pop_calstack(stack);
    }
}

void destroy_calstack(STACK **ppstack) {
    read_calstack(*ppstack);
    free(*ppstack);
    *ppstack = NULL;
}

