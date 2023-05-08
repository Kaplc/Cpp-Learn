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

DARRAY * init_dynamicArray();

void insert_dynamicArray();

void delete__dynamicArray();

void destroy_dynamicArray();

void run_dynamicArray();
#endif //LINUX_CPPLEARN_DYNAMICARRAY_H
