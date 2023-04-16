//
// Created by kaplc on 2023/4/16.
//
#include <stdio.h>
#include <stdlib.h>

struct std {
    int id;
    char *name;
};

struct class {
    int class_id;
    struct std *std;
} class1;

void run(){
    char a = 0;
    struct std* stdp = NULL;
    struct class class2;
    class1.class_id = 1;
    (&class2)->class_id = 2;
    stdp = (struct std *)malloc(sizeof(struct std));
    class1.std = stdp;
//    strcpy(class1.std->name, "abc"); // class1.std->name获取的是数组首地址
//    (class1.std->name)[2] = '1';
    class1.std->name = "abc"; // 字符串常量
//    a=*((class1.std->name) + 1)  ;
    printf("%s", class1.std->name);

}
