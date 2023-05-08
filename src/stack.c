//
// Created by kaplc on 2023/5/7.
//

#include <stdlib.h>
#include <stdio.h>
#include "../header/stack.h"



void init_stack(STACK **ppstack) {
    // 初始化栈
    STACK *stack = malloc(sizeof(struct stack));
    stack->size = 0;
    stack->header.next = NULL;

    *ppstack = stack;
}

void push_stack(STACK *stack, void *data) {
    if (stack == NULL)return;

    // 初始化新节点
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = NULL;
    // 连接
    NODE *current = &(stack->header);
    new_node->next = current->next;
    current->next = new_node;

    stack->size++;
}

void pop_stack(STACK *stack) {
    if (stack == NULL)return;

    NODE *current = &(stack->header);
    // 从头节点指向第一个节点
    current = current->next;
    printf("%d\n", *((int *) (current->data)));
    // 头结点指向第二个节点
    stack->header.next = current->next;
    stack->size--;
    // 释放第一个节点
    free(current);

}

void read_stack(STACK *stack) {
    if (stack == NULL)return;

    int total_size = stack->size;
    for (int i = 0; i < total_size; ++i) {
        pop_stack(stack);
    }
}

void destroy_stack(STACK **ppstack) {
    read_stack(*ppstack);
    free(*ppstack);
    *ppstack = NULL;
}

void run_stack() {
    STACK *stack = NULL;
    init_stack(&stack);

    int data = 1, d2 = 2, d3 = 3;
    push_stack(stack, &data);
    push_stack(stack, &d2);
    push_stack(stack, &d3);

    read_stack(stack);
    destroy_stack(&stack);
}