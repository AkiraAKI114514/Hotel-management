#include <string.h>
#include <stdio.h>
#include "msg.h"

#define ADMIN_ID "admin"
#define ADMIN_PWD "123456789"
#define MAX_ID_LEN 15
#define MAX_PWD_LEN 20
#define MAX_ROOMS 200
#define MAX_EPLY_NUMBER 50
#define MAX_NAME_LEN 50
#define FLOORS 4

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
    char room_number[4];
} Customer;

Employee eply_Info[MAX_EPLY_NUMBER];
Customer cus_Info[MAX_ROOMS];

int rooms[MAX_ROOMS];

char* index_to_room(int index) {
    int rooms_per_floor = MAX_ROOMS / FLOORS;
    int floor_number = index / rooms_per_floor;
    char prefix[4] = {'G', '1', '2', '3'};
    char floor = prefix[floor_number];
    int room_number = index % rooms_per_floor + 1;
    static char room[4];

    sprintf(room, "%c%02d", floor, room_number);
    return room;
}

int room_to_index(char *room) {
    int rooms_per_floor = MAX_ROOMS / FLOORS;
    int index;
    int floor;
    int room_number = atoi(&room[1]);
    char prefix[4] = {'G', '1', '2', '3'};
    
    for (int i = 0; i < FLOORS; i++) {
        if (prefix[i] == room[0]) {
            floor = i;
            break;
        }
    }

    index = floor * rooms_per_floor + room_number - 1;
    return index;
}


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
    } else if (strcmp(identity, "Customer") == 0) { 
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (strcmp(cus_Info[i].ID, ID) == 0) {
                return i;
            }
        }
    }
    return -1;
}

int login(char *identity, char *ID){
    char pwd[MAX_PWD_LEN];

    while (1) {
        printf("[INPUT] Please enter your %s ID >> ", identity);
        scanf(" %[^\n]", ID);
        
        if (strcmp(ID, "Exit") == 0) {
            printf("[INFO] Returning to main menu.\n");
            return 0;
        }

        printf("[INPUT] Please enter your password >> ");
        scanf(" %[^\n]", pwd);

        if (strcmp(pwd, "Exit") == 0) {
            printf("[INFO] Returning to main menu.\n");
            return 0;
        }

        if (strcmp(identity, "Admin") == 0) {
            if (strcmp(ID, ADMIN_ID) == 0) {
                if (strcmp(pwd, ADMIN_PWD) == 0) {
                    printf("[INFO] Welcome, Administrator.\n");
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
                        printf("[INFO] Welcome, %s: %s.\n",identity,eply_Info[pos].name);
                        return 1;
                    }
                } else {
                    if (strcmp(pwd, cus_Info[pos].password) == 0) {
                        printf("[INFO] Welcome, %s: %s.\n",identity,cus_Info[pos].name);
                        return 1;
                    }
                }
                printf("[ERROR] Wrong password, please try again!\n");
                return 0;
            }
        }
        printf("[ERROR] Unknown %s ID, please try again!\n", identity);
        return 0;
    }
}
