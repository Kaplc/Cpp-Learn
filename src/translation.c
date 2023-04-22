#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define DICT_PATH "../cpp_learn/file/dict.txt"
//#define DICT_PATH "G:\\project\\cpp_learn\\file\\dict.txt"
#define DICT_LINE 111102

typedef struct once_word {
    char *word;
    char *trans;
} ONCE_WORD;

int str_filter_start(char buf[]) {
    // 去除开头
    for (int i = 0; i < strlen(buf); ++i) {
        if (*(buf + i) == ':') {
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

        once_line = fgets(buf_eng, sizeof(buf_eng), fp); // 读取单行

        if (!once_line)return NULL; // 检测到行尾

        str_filter_end(buf_eng); // 过滤器

        p_dict[i].word = (char *) malloc(strlen(buf_eng) + 1);
        strcpy(p_dict[i].word, buf_eng + 1); // 移动指针去除

        // 下一行
        next_line = fgets(buf_chi, sizeof(buf_chi), fp);

        if (!next_line)return NULL;

        str_filter_end(buf_chi);
        start = str_filter_start(buf_chi); // 去除开头

        p_dict[i].trans = (char *) malloc(strlen(buf_chi) + 1 - start);
        strcpy(p_dict[i].trans, buf_chi + start + 1);
    }

    return p_dict;
}

void get_word(char word[], int size) {
    char buf[1024] = {0};
    printf("请输入要翻译的内容:");
    fflush(stdout);
    fgets(word, size, stdin);
    str_filter_end(word);// stdin中获取word[]

}

char *query_dict(ONCE_WORD *p_dict, char input_word[]) {
    int dict_word_cur = 0; //字典单词大游标
    int input_word_cur = 0; // 输入单词游标
    int dict_word_subcur = 0; // 字典单词小游标
    char *p_res = NULL;

    for (int i = 0; i < DICT_LINE; i++) {

        // 下组比较前游标置零
        dict_word_cur = 0;
        input_word_cur = 0;
        dict_word_subcur = 0;

        while (dict_word_cur < strlen(p_dict[i].word)) { // 字典单词游标不超过单词长度
            while (*(p_dict[i].word + dict_word_subcur) == *(input_word + input_word_cur)) { // 字典单词浮动游标与输入单词游标进行比较,
                // 相等移动都移动到下一位
                dict_word_subcur++;
                input_word_cur++;

                // 判断浮动和输入游标是否同时结尾
                if (*(p_dict[i].word + dict_word_subcur) == 0 && *(input_word + input_word_cur) == 0) {
                    p_res = p_dict[i].trans;
                    return p_res;
                }
            }

            input_word_cur = 0;// 输入单词游标回到开头
            dict_word_subcur = dict_word_cur++; // 字典单词游标下移, 并将浮动游标同步

        }

    }
    return NULL;
}

void run_translations(void) {
     // 设置windows终端编码
    char *p_res = NULL;
    char word[1024] = {0};
    ONCE_WORD *p_dict = NULL;

    p_dict = loan_dict(); // 加载字典

    for (int i = 0; i < 50; ++i) {
        get_word(word, sizeof(word)); // 加载键盘
        p_res = query_dict(p_dict, word); // 查询

        if (p_res == NULL) {
            printf("未找到!\n");
            continue;
        }
        printf("%s\n", p_res);
        fflush(stdout);
    }
}