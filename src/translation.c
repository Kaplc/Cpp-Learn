#include<stdio.h>
#define DICT_PATH "G:\\project\\cpp_learn\\file\\dict.txt"
#define DICT_LINE 11102

typedef struct word
{
	char* english;
	char* chinese;
}WORD;

WORD* loan_dict() {

	FILE* fp = fopen(DICT_PATH, "r");

	if (!fp) {
		printf("词典未找到,请检查词典位置!\n程序自动关闭...");
		exit(1);
	}

	WORD* words = (WORD*)malloc(sizeof(WORD) * DICT_LINE); // 创建结构体数组
	
	for (int i = 0; i < DICT_LINE; i++) {

		char buf_eng[1024] = { 0 };
		char buf_chi[1024] = { 0 };
		char* once_line = NULL;
		char* next_line = NULL;

		// 英文
		once_line = fgets(buf_eng, sizeof(buf_eng), fp); // 读取的每一行

		if (!once_line)return; // 读取到末尾

		for (int end = strlen(buf_eng)-1; 1; end--) { // 过滤
			if (!(*(buf_eng + end) == ' ' || *(buf_eng + end) == '\t' || *(buf_eng + end) == '\n')) { // 字符串移动尾部指针查找有效字符
				*(buf_eng + (end + 1)) = 0; // 重定义字符串结尾处
				break;
			}
		}

		words[i].english = (char*)malloc(strlen(buf_eng)+1);
		strcpy(words[i].english, buf_eng);

		// 中文
		next_line = fgets(buf_chi, sizeof(buf_chi), fp);// 下一行

		if (!next_line)return;

		for (int end = strlen(buf_chi); 1; end--) { // 过滤
			if (!(*(buf_chi + end) == " " || *(buf_chi + end) == "\t" || *(buf_chi + end) == "\n")) { // 字符串移动尾部指针查找有效字符
				*(buf_chi + (end + 1)) = 0; // 重定义字符串结尾处
				break;
			}
		}
		words[i].chinese = (char*)malloc(strlen(buf_chi));
		strcpy(words[i].chinese, buf_eng);
	}

	return words;
}

void get_word(char word[], int size) {
	printf("请输入要翻译中文:");
	char* p_word = fgets(word, size, stdin); // stdin读取字符串并写入word[]
	if (!p_word)exit();
}

void serch_dict() {

}

void run_translations(void) {
	char word[1024] = { 0 };
	WORD* words = NULL;

	words = loan_dict();
	get_word(word, sizeof(word));
	serch_dict(words);

}