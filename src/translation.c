#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_PATH "../file/dict.txt"
//#define DICT_PATH "G:\\project\\cpp_learn\\file\\dict.txt"
#define DICT_LINE 11102

typedef struct word {
    char *english;
    char *chinese;
} WORD;

WORD *loan_dict() {

    FILE *fp = fopen(DICT_PATH, "r");

    if (!fp) {
        printf("�ʵ�δ�ҵ�,����ʵ�λ��!\n�����Զ��ر�...");
        exit(0);
    }

    WORD *words = (WORD *) malloc(sizeof(WORD) * DICT_LINE); // �����ṹ������

    for (int i = 0; i < DICT_LINE; i++) {

        char buf_eng[1024] = {0};
        char buf_chi[1024] = {0};
        char *once_line = NULL;
        char *next_line = NULL;

        // Ӣ��
        once_line = fgets(buf_eng, sizeof(buf_eng), fp); // ��ȡ��ÿһ��

        if (!once_line)return NULL; // ��ȡ��ĩβ

        for (int end = strlen(buf_eng) - 1; 1; end--) { // ����
            if (!(*(buf_eng + end) == ' ' || *(buf_eng + end) == '\t' ||
                  *(buf_eng + end) == '\n')) { // �ַ����ƶ�β��ָ�������Ч�ַ�
                *(buf_eng + (end + 1)) = 0; // �ض����ַ�����β��
                break;
            }
        }

        words[i].english = (char *) malloc(strlen(buf_eng) + 1);
        strcpy(words[i].english, buf_eng + 1); // 移动指针去除

        // ����
        next_line = fgets(buf_chi, sizeof(buf_chi), fp);// ��һ��

        if (!next_line)return NULL;

        for (int end = strlen(buf_chi); 1; end--) { // ����
            if (!(*(buf_chi + end) == ' ' || *(buf_chi + end) == '\t' ||
                  *(buf_chi + end) == '\n')) { // �ַ����ƶ�β��ָ�������Ч�ַ�
                *(buf_chi + (end + 1)) = 0; // �ض����ַ�����β��
                break;
            }
        }
        words[i].chinese = (char *) malloc(strlen(buf_chi) + 1);
        strcpy(words[i].chinese, buf_chi + 5);
    }

    return words;
}

void get_word(char word[], int size) {
    printf("������Ҫ��������:");
    char *p_word = fgets(word, size, stdin); // stdin��ȡ�ַ�����д��word[]
    if (!p_word)exit(0);
}

void serch_dict() {

}

void run_translations(void) {
    char word[1024] = {0};
    WORD *words = NULL;

    words = loan_dict();
    get_word(word, sizeof(word));
    serch_dict(words);

}