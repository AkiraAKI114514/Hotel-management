#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "msg.h"

#define ADMIN_ID "admin"
#define ADMIN_PWD "123456789"
#define MAX_ID_LEN 15
#define MAX_PWD_LEN 20
#define MAX_NAME_LEN 50
#define MAX_ROOMS 200
#define MAX_CUSTOMERS 500
#define MAX_EPLYS 50
#define FLOORS 4
#define DEFAULT_STAT "Empty"
#define LIVEIN_STAT "Livein"
#define BOOKED_STAT "Booked"

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

typedef struct {
   char room_number[4];
   char room_status[10];
} Room;


Employee eply_Info[MAX_EPLYS];
Customer cus_Info[MAX_CUSTOMERS];
Room room_Info[MAX_ROOMS];

int rooms[MAX_ROOMS] = {0};

char *index_to_room(int index) {
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

int find_empty_rooms() {
    int tempend = 0;
    int tempst = 0;
    int rooms = MAX_ROOMS;
    int floor = 0;
    printf("Empty rooms:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        // printf("%d", i);
        if (strcmp(room_Info[i].room_status, DEFAULT_STAT) == 0) {
            if ((i + 1) % 50 == 0) {
                if (tempst != tempend) {
                    char *st = index_to_room(tempst);
                    printf("%s", st);
                    char *end = index_to_room(tempend);
                    printf("-%s\n", end);
                } else {
                    char *end = index_to_room(tempend);
                    printf("%s\n", end);
                }
                tempst = i + 1;
            }
        } else {
            if (tempend - 1 == tempst) {
                printf("%s ", index_to_room(tempst));
                tempst = i + 1;
            } else {
                char *st1 = index_to_room(tempst);
                printf("%s-", st1);
                char *end1 = index_to_room(tempend - 1);
                printf("%s ", end1);

                tempst = i + 1;
            }
            
            if ((i + 1) % 50 == 0) {
                printf("\n");
            }
        }
        tempend += 1;
    }
    return 0;
}

int init() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        strcpy(room_Info[i].room_status, DEFAULT_STAT);
        strcpy(room_Info[i].room_number, index_to_room(i));
    }
    for (int j = 0; j < MAX_EPLYS; j++) { 
        strcpy(eply_Info[j].department, "NONE");
    }
    for (int k = 0; k < MAX_CUSTOMERS; k++) {
        cus_Info[k].number = 0;
    }
}

void view_cus_info() {
    int has_customer = 0;
    printf("======== Customers' Information ========\n");

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (cus_Info[i].number != 0) {
            has_customer = 1;
            int room_index = room_to_index(cus_Info[i].room_number);

            printf("----------------------------------------\n");
            printf("Customer #%d:\n", i + 1);
            printf("  ID          : %s\n", cus_Info[i].ID);
            printf("  Name        : %s\n", cus_Info[i].name);
            printf("  Phone Number: %d\n", cus_Info[i].number);
            printf("  Room        : %s (%s)\n", cus_Info[i].room_number, room_Info[room_index].room_status);
            printf("  Bill        : %d\n", cus_Info[i].bill);
            printf("----------------------------------------\n\n");
        }
    }

    if (!has_customer) {
        printf("[INFO] No customers are currently checked in.\n");
    }

    printf("========================================\n");
}

void view_accom_info() {
    printf("======== Accommodation List ========\n");

    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %s : %s\n", room_Info[i].room_number, room_Info[i].room_status);
        
    }
    printf("====================================\n\n");
}

int int_input_check(int *input) { // check whether the input is valid when needs a integer
    if (scanf("%d", input) != 1) {
        printf("[ERROR] Invalid input,please try again!\n");
        while (getchar() != '\n');
        return 0;
    }
    else {
        return 1;
    }
}

int find_ID(char *identity, char *ID) {
    if (strcmp(identity, "Employee") == 0) {
        for (int i = 0; i < MAX_EPLYS; i++) {
            if (strcmp(eply_Info[i].ID, ID) == 0) {
                return i;
            }
        }
    }
    else if (strcmp(identity, "Customer") == 0) {
        for (int i = 0; i < MAX_CUSTOMERS; i++) {
            if (strcmp(cus_Info[i].ID, ID) == 0) {
                return i;
            }
        }
    }
    return -1;
}

int valid_room_check(char *room) {
    char prefix;
    char valid[4] = {'G', '1', '2', '3'};           
    int number;
    int flag = -1;

    if (strlen(room) != 3) return 0;

    prefix = room[0];
    if (sscanf(&room[1], "%d", &number) <= 0) return 0;

    for (int i = 0; i < 4; i++) {
        if (valid[i] == prefix) {
            flag++;
            break;
        }
    }

    if (number >= 1 && number <= 50) {
        flag++;
    }

    return flag;
}

int login(char *identity, char *ID) {
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
                        printf("[INFO] Welcome, %s: %s.\n", identity, eply_Info[pos].name);
                        return 1;
                    }
                } else {
                    if (strcmp(pwd, cus_Info[pos].password) == 0) {
                        printf("[INFO] Welcome, %s: %s.\n", identity, cus_Info[pos].name);
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
