#include <stdlib.h>
#include <stdio.h>

#include "../header/link.h"

// 连接器
typedef struct linknode {
    struct linknode *next;
} LINKNODE;
// 数据节点
typedef struct datanode {
    struct linknode node;
    void *data;
} DATANODE;
// 维护器
typedef struct maintenance {
    struct datanode header;
    int size;
} MAINTENANCE;
// 测试数据
typedef struct person {
    char name[64];
    int id;
} PERSON;

void print_person(DATANODE *data) {
    PERSON *person_data = data->data;
    printf("姓名：%s 学号：%d\n", person_data->name, person_data->id);

}

void print_int(void *data) {
    int *intdata = data;
    printf("整数：%d\n", *intdata);
}

void print_double(void *data) {
    double *doubledata = data;
    printf("浮点数：%lf\n", *doubledata);
}

void print_chars(void *data) {
    char *chardata = data;
    printf("字符串：%s\n", chardata);
}

void clear_list(MAINTENANCE *list) {

    LINKNODE *current = list->header.node.next;
    list->header.node.next = NULL;
    for (int i = 0; i < list->size; ++i) {
        DATANODE *temp = (DATANODE *) current;
        current = current->next;
        free(temp);
    }
    list->size = 0;
    printf("清空完成");

}

void delete_list(MAINTENANCE **list) {
    if (list != NULL) {
        free(*list);

    };
    printf("链表删除成功");
    *list = NULL;
}

void pop_link_pos(MAINTENANCE *list, int pos) {
    if (list == NULL) {
        printf("链表为空");
        return;
    }
    if (pos > list->size || pos < 1) {
        printf("删除位置非法");
        return;
    }
    LINKNODE *front = list->header.node.next; // 前驱指针
    LINKNODE *after = (LINKNODE *) &(list->header); // 后驱指针

    for (int i = 1; i < pos; ++i) {
        after = front;
        front = front->next;
    }
    after->next = front->next; // 修改后驱指针指向
    free((DATANODE *) front);
    list->size--;
}
void pop_link_content(MAINTENANCE *list, void *content) {
    if (list == NULL) {
        printf("链表为空");
        return;
    }

    LINKNODE *front = list->header.node.next; // 前驱指针
    LINKNODE *after = (LINKNODE *) &(list->header); // 后驱指针

    for (int i = 1; i < list->size; ++i) {
        if (((DATANODE *)front)->data == content){
            printf("删除内容----：");
            print_person((DATANODE *)front);
            break;
        }
        after = front;
        front = front->next;

    }
    after->next = front->next; // 修改后驱指针指向
    free((DATANODE *) front);
    list->size--;
}
void insert_link(MAINTENANCE *list, void *data, int pos) {
    if (list == NULL) {
        printf("链表为空");
        return;
    }
    DATANODE *new_datanode = malloc(sizeof(DATANODE)); // 创建新数据节点
    new_datanode->data = data;
    new_datanode->node.next = NULL;

    LINKNODE *current = (LINKNODE *) &(list->header);
    if (pos < 1) pos = 1;
    if (pos > list->size)pos = list->size + 1;

    for (int i = 1; i < pos; ++i) { // 移动链表指针到目标位置
        current = current->next;
    }
    // 连接链表
    new_datanode->node.next = current->next;
    current->next = (LINKNODE *) new_datanode;// 指向数据节点的前面属于LINKNODE的内存空间

    list->size++;
}

void print_link(MAINTENANCE *list, void (*print_func)(DATANODE *)) {
    if (list == NULL) {
        printf("链表为空");
        return;
    }
    LINKNODE *current = (LINKNODE *) &(list->header);
    for (int i = 1; i <= list->size; ++i) {
        current = current->next; // 移动指针
        // 通过node找到节点首地址，强转成DATANODE *改变指针步长读取所有数据
        print_func((DATANODE *) current); // 回调函数处理不同类型数据
    }
}

void run_link() {
    // 初始化链表
    MAINTENANCE *list = malloc(sizeof(MAINTENANCE));
    list->size = 0;
    list->header.data = NULL;
    list->header.node.next = NULL;
    // 输入数据
    PERSON data1 = {"xiaoming", 1};
    PERSON data2 = {"xiaohong", 2};
    PERSON data3 = {"xiaoa", 3};
    PERSON data4 = {"xiaob", 4};
    PERSON data5 = {"xiaoc", 5};
//    int pos = 3;
    int data = 3;
    // 插入链表
    insert_link(list, &data1, 1);
    insert_link(list, &data2, 2);
    insert_link(list, &data3, -9);
    insert_link(list, &data4, 100);
    insert_link(list, &data5, 2);
//    35124
    // 查询链表
    print_link(list, print_person);
    pop_link_content(list, &data1);
    printf("\n");
    print_link(list, print_person);
    clear_list(list);
    printf("\n");
    print_link(list, print_person);
    delete_list(&list);
    printf("\n");
    print_link(list, print_person);
}