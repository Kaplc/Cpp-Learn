# include <stdio.h>

//��Windows��system("pause")
void pause() {

    printf("\n�������������...\n");
    getchar();
}

//���ж��Ƿ�򿪳ɹ�
FILE *open_file(char *path, char *type) {

    FILE *fp = fopen(path, type);
    if(fp==NULL){
        printf("�ļ���ʧ�ܣ�.");
        return NULL;
    }
    return fp;
}