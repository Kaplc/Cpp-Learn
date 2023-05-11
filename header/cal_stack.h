//
// Created by kaplc on 2023/5/7.
//
#pragma once
#ifndef LINUX_CPPLEARN_STACK_H
#define LINUX_CPPLEARN_STACK_H
typedef struct node {
    struct node *next;
    void *data;
    char type;
} NODE;

typedef struct stack {
    NODE header;
    int size;
} STACK;

void run_stack();

STACK *init_calstack();

NODE *generate_node(void *data, char type);

void push_calstack(STACK *stack, NODE* node);

NODE * pop_calstack(STACK *stack);

NODE * read_calstack_top(STACK *stack);

void read_calstack(STACK *stack);

void destroy_calstack(STACK **ppstack);
#endif //LINUX_CPPLEARN_STACK_H
