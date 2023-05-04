#include <stdlib.h>

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

void create_data(MAINTENANCE *list, void *data) {
    data = (PERSON *) data; // 转换指针类型
    DATANODE *new_datanode = malloc(sizeof(DATANODE)); // 创建新数据节点
    new_datanode->data = data;
    new_datanode->node.next = NULL;

    list->header.node.next = (LINKNODE *) new_datanode; // 指向数据节点的前面属于LINKNODE的内存空间
    list->size++;

}

void read_link(MAINTENANCE *list) {
    PERSON *data = NULL;
    DATANODE *current = &(list->header);
    for (int i = 0; i < list->size; ++i) {
        current = (DATANODE *) current->node.next;
        data = current->data;
    }
}

void run_link() {
    // 初始化链表
    MAINTENANCE *list = malloc(sizeof(MAINTENANCE));
    list->size = 0;
    list->header.data = NULL;
    list->header.node.next = NULL;
    // 输入数据
    PERSON student = {"xiaoming", 1};
    // 插入链表
    create_data(list, &student);
    // 查询链表
    read_link(list);

}