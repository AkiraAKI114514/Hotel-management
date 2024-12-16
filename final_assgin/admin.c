#include <stdio.h>

int v_accinfo(){
    char intro[200];
    int rs[10];
    int re[10];
    int nb[5];
    int nl[5];
    int members[30];
    FILE *info;
    info = fopen("accomoinfo.txt", "r");
    if (info == NULL){
        printf("Invalid file.\n");
        return 0;
    }else{
        char tg = ')';
        char cu;
        long pos = -1;
        while(fgetc(info) != EOF){
            while ((cu = fgetc(info)) != EOF){
                if(cu == tg){
                    pos = ftell(info) - 1;
                    break;
                }
            
            }
        }
    }
    fclose(info);
    return 0;
}

int admin(){
    printf("This is the Administrator's mode.\n");
    getchar();
    v_accinfo();
}

int start_login(){
    char *line = "=====================================\n";
    printf("%sThis is the hotel management system.\n",line);
    getchar();
    admin();

    return 0;
}


int main(){
    start_login();
    return 0;
}