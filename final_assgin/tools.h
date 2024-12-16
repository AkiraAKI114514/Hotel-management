#include <string.h>
#include <stdio.h>
#include "msg.h"

#define ADMIN_ID "admin"
#define ADMIN_PWD "123456789"
#define MAX_ID_LEN 15
#define MAX_PWD_LEN 20
#define MAX_ROOM_S 256
#define MAX_ROOM_E 64
#define MAX_EPLY_NUMBER 50
#define MAX_NAME_LEN 50

typedef struct {
    char department[100];
    char name[MAX_NAME_LEN];
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
} Employee;

typedef struct {
    int number;
    int bill;
    char name[MAX_NAME_LEN];
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
    char room_number;
} Customer;

Employee eply_Info[MAX_EPLY_NUMBER];
Customer cus_Info[MAX_ROOM_E + MAX_ROOM_S];

int int_input_check(int *input) {   //check whether the input is valid when needs a integer
    if (scanf("%d", input) != 1) {
        printf("[ERROR] Invalid input,please try again!\n");

        while (getchar() != '\n');
        return 0;
    } else {
        return 1;
    }
}

int find_ID(char *identity, char *ID) {
    if (strcmp(identity, "Employee") == 0) {
        for (int i = 0; i < MAX_EPLY_NUMBER; i++) {
            if (strcmp(eply_Info[i].ID, ID) == 0) {
                return i;
            }
        }
        return -1;
    } else if (strcmp(identity, "Customer") == 0) { 
        for (int i = 0; i < MAX_ROOM_E + MAX_ROOM_S; i++) {
            if (strcmp(cus_Info[i].ID, ID) == 0) {
                return i;
            }
        }
        return -1;
    }
}

int login(char *identity, char *ID, char *password){
    char pwd[MAX_PWD_LEN];

    while (1) {
        printf("[INPUT] Please enter your %s ID >> ", identity);
        fgets(ID, MAX_ID_LEN, stdin);

        if (strcmp(ID, "Exit") == 0) {
            printf("[INFO] Returning to main menu.\n");
            return 0;
        }

        printf("[INPUT] Please enter your password >> \n");
        fgets(pwd, MAX_PWD_LEN, stdin);

        if (strcmp(pwd, "Exit") == 0) {
            printf("[INFO] Returning to main menu.\n");
            return 0;
        }

        if (strcmp(identity, "Admin") == 0) {
            if (strcmp(ID, ADMIN_ID) == 0) {
                if (strcmp(pwd, ADMIN_PWD) == 0) {
                    printf("[INFO] Welcome, Administrator\n");
                    return 1; 
                } else {
                    printf("[ERROR] Wrong password, please try again!\n");
                    return 0;
                }
            }
        } else if (strcmp(identity, "Employee") == 0 || strcmp(identity, "Customer") == 0) {
            int pos = find_ID(identity, ID);

            if (pos != -1) {
                if (strcmp(identity, "Employee") == 0) {
                    if (strcmp(pwd, eply_Info[pos].password) == 0) {
                        printf("[INFO] Welcome, %s: %s\n",identity,eply_Info[pos].name);
                        return 1;
                    }
                } else {
                    if (strcmp(pwd, cus_Info[pos].password) == 0) {
                        printf("[INFO] Welcome, %s: %s\n",identity,cus_Info[pos].name);
                        return 1;
                    }
                }
                printf("[ERROR] Wrong password, please try again!\n");
                return 0;
            }
        }
        printf("[ERROR] Unknown %s ID, please try again!\n", identity);
    }
}
