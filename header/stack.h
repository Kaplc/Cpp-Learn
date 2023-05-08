//
// Created by kaplc on 2023/5/7.
//
#pragma once
#ifndef LINUX_CPPLEARN_STACK_H
#define LINUX_CPPLEARN_STACK_H
typedef struct node {
    struct node *next;
    void *data;
} NODE;

typedef struct stack {
    NODE header;
    int size;
} STACK;

void run_stack();
void init_stack(STACK **ppstack);
void destroy_stack(STACK **ppstack);
void read_stack(STACK *stack);
void pop_stack(STACK *stack);
void push_stack(STACK *stack, void *data);
#endif //LINUX_CPPLEARN_STACK_H
