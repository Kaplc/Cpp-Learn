//
// Created by kaplc on 2023/5/11.
//
#include <stdio.h>
#include <stdlib.h>

#include "../header/cal_link.h"
#include "../header/cal_stack.h"



LINKLIST *init_calLink() {
    LINKLIST *linklist = malloc(sizeof(LINKLIST));
    linklist->header.type = 'h';
    linklist->header.data = NULL;
    linklist->header.next = NULL;
    linklist->size = 0;
    return linklist;

}

void add_node(LINKLIST *linklist, NODE *node) {// 尾插
    NODE *current = &(linklist->header);
    while (current->next != NULL) { // 移动到尾部
        current = current->next;
    }
    current->next = node;
}

