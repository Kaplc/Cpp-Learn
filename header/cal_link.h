//
// Created by kaplc on 2023/5/11.
//

#ifndef LINUX_CPPLEARN_CAL_LINK_H
#define LINUX_CPPLEARN_CAL_LINK_H

#include "cal_stack.h"

typedef struct linklist {
    NODE header;
    int size;
} LINKLIST;

void add_node(LINKLIST *linklist, NODE *node);

LINKLIST *init_calLink();

#endif //LINUX_CPPLEARN_CAL_LINK_H
