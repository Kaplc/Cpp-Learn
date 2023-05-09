//
// Created by kaplc on 2023/5/8.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../header/dynamicArray.h"

#define CAPACITY 2

DARRAY *init_dynamicArray() {
    DARRAY *darray = malloc(sizeof(DARRAY));
    darray->size = 0;
    darray->capacity = CAPACITY;
    darray->dArray = malloc(sizeof(void *) * CAPACITY);
    return darray;
}

void extend_dynamicArray(DARRAY *darray) {
    void **new_array = malloc(sizeof(void *) * ((darray->capacity) + CAPACITY));
    memcpy(new_array, darray->dArray, sizeof(void *) * (darray->capacity)); // 复制内存
    free(darray->dArray);
    darray->dArray = new_array; // 重新指向新内存
    darray->capacity = (darray->capacity) + CAPACITY; // 修改容量

}

void insert_dynamicArray(DARRAY *darray, void *data, int pos) {
    if (darray == NULL)return;
    // 判断是否还有容量
    if (darray->capacity == darray->size) {
        extend_dynamicArray(darray);
    }

    if (pos > darray->size) {
        // 大于下标尾插
        darray->dArray[darray->size] = data;
    } else if (pos <= 0) {
        // 小于等于0头插
        // 移动所有元素
        for (int i = 0; 0 < darray->size - i; i++) {
            darray->dArray[darray->size - i] = darray->dArray[darray->size - i - 1];
        }
        darray->dArray[0] = data;
    } else {
        // 移动目标位置以后所有元素
        for (int i = 0; pos <= darray->size - i; i++) {
            darray->dArray[darray->size - i] = darray->dArray[darray->size - i - 1];
        }
        darray->dArray[pos - 1] = data;
    }
    darray->size++;

}

void pop_dynamicArray_pos(DARRAY *darray, int pos) {
    if (darray == NULL)return;
    if (pos <= 0 && pos > darray->size) {
        printf("删除位置非法");
    }
    pos--; // pos下标1为数组的0
    for (int i = 0; i < (darray->size - pos); ++i) {
        darray->dArray[pos + i] = darray->dArray[pos + 1 + i];
    }
    darray->size--;
}

void pop_dynamicArray_content(DARRAY *darray, void *content) {
    if (darray == NULL)return;
    int exist = 0; // 判断是否存在该值标识
    for (int i = 0; i < darray->size; ++i) {
        if (darray->dArray[i] != content && exist == 0) {
            continue; // 值不同继续循环
        }
        darray->dArray[i] = darray->dArray[i + 1]; // 后往前覆盖
        exist = 1;
    }
    if (exist == 1) {
        darray->size--;
    }

}

void read_dynamicArray(DARRAY *darray) {
    for (int i = 0; i < darray->size; ++i) {

        printf("%d", *(int *) darray->dArray[i]);
    }
}

void destroy_dynamicArray(DARRAY **ppdarray) {
    if (*ppdarray == NULL)return;

    free((*ppdarray)->dArray);
    free(*ppdarray);
    printf("\n动态数组已销毁");
    *ppdarray = NULL;
}

void run_dynamicArray() {
    DARRAY *darray = NULL;
    darray = init_dynamicArray();
    int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6;
    insert_dynamicArray(darray, &a1, 1);
    insert_dynamicArray(darray, &a2, 0);
    insert_dynamicArray(darray, &a3, 3);
    insert_dynamicArray(darray, &a4, 100);
    insert_dynamicArray(darray, &a5, -2);
    insert_dynamicArray(darray, &a6, 5);
    //521364
    read_dynamicArray(darray);
    printf("\n---------------\n");
    pop_dynamicArray_content(darray, &a2);
    read_dynamicArray(darray);
    destroy_dynamicArray(&darray);
}