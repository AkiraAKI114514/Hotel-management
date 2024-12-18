#include <stdio.h>

void welcomeMsg(){
    printf("===================================================================\n");
    printf("|---------------------Hotel-Management-System---------------------|\n");
    printf("|--Developed-by-AIT2409005_ChengBingzhang-&-AIT2409017_JiChengyi--|\n");
    printf("|--------------------------alpha-version--------------------------|\n");
    printf("===================================================================\n");
}

void menuHelpMsg() {
    printf("[MAIN MENU]\n");
    printf("1. Administrator Access\n");
    printf("2. Employee Access\n");
    printf("3. Customer Access\n");
    printf("4. Exit\n");
    printf("[INPUT] Please select an option (1-4) >> ");
}

void adminHelpMsg(){
    printf("[Administrator Menu]\n");
    printf("1. Record Room Infomation\n");
    printf("2. View Customers' infomation\n");
    printf("3. Exit\n");
    printf("[INPUT] Please select an option (1-3) >>");
}

void RoomstatMsg(){
    printf("[Select the status]\n");
    printf("1. Empty\n");
    printf("2. Booked\n");
    printf("3. Livein\n");
    printf("[INPUT] Please select an option (1-3) >>");
}
