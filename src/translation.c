#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define DICT_PATH "../file/dict.txt"
//#define DICT_PATH "G:\\project\\cpp_learn\\file\\dict.txt"
#define DICT_LINE 11102

typedef struct once_word {
    char *english;
    char *chinese;
} ONCE_WORD;

int str_filter_start(char buf[]) {
    // 去除开头
    for (int i = 0; i < strlen(buf); ++i) {
        if (*(buf + i) == ' ') {
            return i;
        }
    }
    return 0;
}

void str_filter_end(char buf[]) {
    // 过滤器
    for (int end = strlen(buf) - 1; 1; end--) { // 过滤
        if (!(*(buf + end) == ' ' || *(buf + end) == '\t' ||
              *(buf + end) == '\n')) {
            *(buf + (end + 1)) = 0; // 标记字符串末尾
            break;
        }
    }
}

ONCE_WORD *loan_dict() {

    FILE *fp = fopen(DICT_PATH, "r");

    if (!fp) {
        printf("词典文件未找到!");
        exit(0);
    }

    ONCE_WORD *p_dict = (ONCE_WORD *) malloc(sizeof(ONCE_WORD) * DICT_LINE); // 生成结构体数组

    for (int i = 0; i < DICT_LINE; i++) {
        int start = 0;
        char buf_eng[1024] = {0};
        char buf_chi[1024] = {0};
        char *once_line = NULL;
        char *next_line = NULL;

        // 读取英文
        once_line = fgets(buf_eng, sizeof(buf_eng), fp); // 读取单行

        if (!once_line)return NULL; // 检测到行尾

        str_filter_end(buf_eng); // 过滤器

        p_dict[i].english = (char *) malloc(strlen(buf_eng) + 1);
        strcpy(p_dict[i].english, buf_eng + 1); // 移动指针去除

        // 中文
        next_line = fgets(buf_chi, sizeof(buf_chi), fp);// 下一行

        if (!next_line)return NULL;

        str_filter_end(buf_chi);
        start = str_filter_start(buf_chi); // 去除开头

        p_dict[i].chinese = (char *) malloc(strlen(buf_chi) + 1 - start);
        strcpy(p_dict[i].chinese, buf_chi + start + 1);
    }

    return p_dict;
}

void get_word(char word[], int size) {

    SetConsoleOutputCP(CP_UTF8); // windows下控制台编码
    printf("请输入要翻译的内容:");
    fflush(stdout);
    fgets(word, size, stdin);
    str_filter_end(word);// stdin中获取word[]

}

char *query_dict(ONCE_WORD *p_dict, char word[]) {
    char *p_res = NULL;
    char test[1024] = {1};
    for (int i = 0; i < DICT_LINE; i++) {

        // 先搜索中文查到返回英文
        if (strstr(p_dict[i].chinese, word)){
            p_res = p_dict[i].english;
            strcpy(test, p_dict[i].english);
            fflush(stdout);
            return p_res;
        }
        if (strstr(p_dict[i].english, word)){
            p_res = p_dict[i].chinese;
            return p_res;
        }
    }
    return NULL;
}

void run_translations(void) {
    char *p_res = NULL;
    char word[1024] = {0};
    ONCE_WORD *p_dict = NULL;

    p_dict = loan_dict(); // 加载字典

    get_word(word, sizeof(word)); // 加载键盘
    p_res = query_dict(p_dict, word); // 查询

    printf("%s\n", p_res);
    fflush(stdout);

}