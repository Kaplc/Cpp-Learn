//
// Created by kaplc on 2023/5/8.
//

#ifndef LINUX_CPPLEARN_DYNAMICARRAY_H
#define LINUX_CPPLEARN_DYNAMICARRAY_H
typedef struct dynamicArray{
    void **dArray;
    int size;
    int capacity;
}DARRAY;

DARRAY *init_dynamicArray();

void extend_dynamicArray(DARRAY *darray);

void insert_dynamicArray(DARRAY *darray, void *data, int pos);

void pop_dynamicArray_pos(DARRAY *darray, int pos);

void pop_dynamicArray_content(DARRAY *darray, void *content);

void read_dynamicArray(DARRAY *darray);

void destroy_dynamicArray(DARRAY **ppdarray);

void run_dynamicArray();
#endif //LINUX_CPPLEARN_DYNAMICARRAY_H
