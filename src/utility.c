# include <stdio.h>

//类Windows中system("pause")
void pause() {

    printf("\n输入任意键继续...\n");
    getchar();
}

//并判断是否打开成功
FILE *open_file(char *path, char *type) {

    FILE *fp = fopen(path, type);
    if(fp==NULL){
        printf("文件打开失败！");
        return NULL;
    }
    return fp;
}