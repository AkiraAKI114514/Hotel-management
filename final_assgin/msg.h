#include <stdio.h>

void WelcomeMsg(){
    printf("===================================================================\n");
    printf("|---------------------Hotel-Management-System---------------------|\n");
    printf("|--Developed-by-AIT2409005_ChengBingzhang-&-AIT2409017_JiChengyi--|\n");
    printf("|--------------------------alpha-version--------------------------|\n");
    printf("===================================================================\n");
}

void MenuHelpMsg() {
    printf("[MAIN MENU]\n");
    printf("1. Administrator Access\n");
    printf("2. Employee Access\n");
    printf("3. Customer Access\n");
    printf("4. Exit\n");
    printf("[INPUT] Please select an option (1-4) >> ");
}

void AdminHelpMsg(){
    printf("[ADMINISTRATOR MENU]\n");
    printf("1. Record Room Infomations\n");
    printf("2. View Customers' Infomations\n");
    printf("3. Exit\n");
    printf("[INPUT] Please select an option (1-3) >> ");
}

void RoomStatMsg(){
    printf("[STATUS]\n");
    printf("1. Empty\n");
    printf("2. Booked\n");
    printf("3. Livein\n");
    printf("[INPUT] Please select an option (1-3) >> ");
}

void EmployHelpMsg1(){
    printf("[EMPLOYEE MENU]\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("[INPUT] Please select an option (1-3) >> ");
}

void EmployHelpMsg2(){
    printf("[EMPLOYEE MENU]\n");
    printf("1. View Customers' Informations\n");
    printf("2. View Accomodations\n");
    printf("3. Exit\n");
    printf("[INPUT] Please select an option (1-3) >> ");
}

void DepartmentMsg(){
    printf("[DEPARTMENTS]\n");
    printf("1. Management\n");
    printf("2. Accounting\n");
    printf("3. Service\n");
}

void CusHelpMsg1(){
    printf("[CUSTOMER MENU]\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("[INPUT] Please select an option (1-3) >> ");
}

void CusHelpMsg2() {
    printf("[CUSTOMER MENU]\n");
    printf("1. View Accomodations\n");
    printf("2. Book Room\n");
    printf("3. Check Bill\n");
    printf("4. Exit\n");
    printf("[INPUT] Please select an option (1-4) >> ");
}