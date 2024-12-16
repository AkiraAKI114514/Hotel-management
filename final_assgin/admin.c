#include "tools.h"

void seekr(FILE *fname,char tg)//find pointer after categories.
{
    int cu;
    int pos = -1;
    while ((cu = fgetc(fname)) != EOF)
    {
        if (cu == tg)
        {
            pos = ftell(fname) - 1;
            break;
        }
    }
}

void enterrds(char varie[]){
    int len = strlen(varie);
    if(varie[len-1]=='\n'){
        varie[len - 1] = '\0';
    }
}

int v_accinfo(){
    char intro[200];
    char rs[10];
    char re[10];
    char nb[5];
    char nl[5];
    char members[30];
    FILE *info;
    info = fopen("accomoinfo.txt", "r");
    if(info != NULL){
        seekr(info,')');
        fgets(intro, 200, info);
        seekr(info,')');
        fgets(rs, 10, info);
        seekr(info,')');
        fgets(re, 10, info);
        seekr(info,')');
        fgets(nb, 5, info);
        seekr(info, ')');
        fgets(nl, 5, info);
        seekr(info, ')');
        enterrds(intro);
        enterrds(rs);
        enterrds(re);
        enterrds(nb);
        enterrds(nl);
        char *line = "*********************************************************************";
        printf("\n\n%s\n---%s---\n%s\n\n", line,intro,line);
        printf("%s\n|Standard room:\t\t\t%s\n",line,rs);
        printf("|Extended room:\t\t\t%s\n", re);
        printf("|Booking number:\t\t%s\n", nb);
        printf("|Live in number:\t\t%s\n%s\n", nl,line);
        printf("Stuff:\n");
        while(fgetc(info) != EOF){
            char mem[30];
            fgets(mem, 30, info);
            printf("%s", mem);
        }
    }
    fclose(info);
    return 0;
}

int w_accinfo(){
    FILE *info = fopen("accomoinfo.txt", "w");

}

int v_custinfo(){
    return 0;
}
int admin(){
    printf("This is the Administrator's mode.\n");
    getchar();
    v_accinfo();
}

int start_login(){
    char *line = "=====================================\n";
    printf("%sThis is the hotel management system.\n%s\n",line,line);
    getchar();
    admin();

    return 0;
}


int main(){
    start_login();
    return 0;
}
