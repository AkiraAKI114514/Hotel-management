#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "msg.h"

#define NONE "NONE"
#define ADMIN_ID "admin"
#define ADMIN_PWD "123456789"
#define MAX_ID_LEN 15
#define MAX_PWD_LEN 20
#define MAX_NAME_LEN 50
#define MAX_ROOMS 200
#define MAX_CUSTOMERS 500
#define MAX_EPLYS 50
#define MAX_NUMBER_LEN 20
#define FLOORS 4
#define ROOM_PRICE 200
#define DEFAULT_STAT "Empty"
#define LIVEIN_STAT "Livein"
#define BOOKED_STAT "Booked"
#define VALID_PREFIX {'G', '1', '2', '3'}

typedef int (*check_func)(char*);

typedef struct
{
    char department[100];
    char name[MAX_NAME_LEN];
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
} Employee;

typedef struct
{
    float bill;
    char number[MAX_NUMBER_LEN];
    char name[MAX_NAME_LEN];
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
    char room_number[4];
} Customer;

typedef struct
{
    char room_number[4];
    char room_status[10];
} Room;

Employee eply_Info[MAX_EPLYS];
Customer cus_Info[MAX_CUSTOMERS];
Room room_Info[MAX_ROOMS];

//Transform index into room number
char *index_to_room(int index)
{
    int rooms_per_floor = MAX_ROOMS / FLOORS;
    int floor_number = index / rooms_per_floor;
    char prefix[FLOORS] = VALID_PREFIX;
    char floor = prefix[floor_number];
    int room_number = index % rooms_per_floor + 1;
    static char room[4];

    sprintf(room, "%c%02d", floor, room_number);
    return room;
}

//Transform room number into index
int room_to_index(char *room)
{
    int rooms_per_floor = MAX_ROOMS / FLOORS;
    int index;
    int floor;
    int room_number = atoi(&room[1]);
    char prefix[FLOORS] = VALID_PREFIX;

    for (int i = 0; i < FLOORS; i++)
    {
        if (prefix[i] == room[0])
        {
            floor = i;
            break;
        }
    }

    index = floor * rooms_per_floor + room_number - 1;
    return index;
}

//Display blocks of empty rooms
void find_empty_rooms() {
    int rooms_per_floor = MAX_ROOMS / FLOORS;
    int st, end;
    char prefix[FLOORS] = VALID_PREFIX;

    printf("=========== Empty Rooms ===========\n");
    for (int floor = 0; floor < FLOORS; floor++) {
        st = floor * rooms_per_floor;
        end = st;

        printf("Floor %c:\n  ", prefix[floor]);

        while (st < (floor + 1) * rooms_per_floor) {
            if (strcmp(room_Info[st].room_status, DEFAULT_STAT) == 0) {
                while (end < (floor + 1) * rooms_per_floor && strcmp(room_Info[end].room_status, DEFAULT_STAT) == 0) {
                    end++;
                }

                char start_room[4], end_room[4];
                strcpy(start_room, index_to_room(st));
                strcpy(end_room, index_to_room(end - 1));

                if (st == end - 1) {
                    printf("%s ", start_room);
                } else {
                    printf("%s-%s ", start_room, end_room);
                }

                st = end;
            } else {
                st++;
                end = st;
            }
        }

        printf("\n");
        if (floor < 3) printf("-----------------------------------\n");
    }
    printf("===================================\n");
}

//Display customer infomations
void view_cus_info() 
{
    int has_customer = 0;
    int room_index;
    printf("======== Customers' Information ========\n");

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (strcmp(cus_Info[i].ID, NONE) != 0) {
            has_customer = 1;
            

            printf("----------------------------------------\n");
            printf("Customer #%d:\n", i + 1);
            printf("  ID          : %s\n", cus_Info[i].ID);
            printf("  Name        : %s\n", cus_Info[i].name);
            printf("  Phone Number: %s\n", cus_Info[i].number);

            if (strcmp(cus_Info[i].room_number, NONE) == 0)
            {
                printf("  Room Number : %s\n", NONE);
            }
            else
            {   
                room_index = room_to_index(cus_Info[i].room_number);
                printf("  Room Number : %s (%s)\n", cus_Info[i].room_number, room_Info[room_index].room_status);
            }

            printf("  Bill        : %.2f\n", cus_Info[i].bill);
            printf("----------------------------------------\n\n");
        }
    }

    if (!has_customer) 
    {
        printf("[INFO] No customers are currently checked in.\n");
    }

    printf("========================================\n");
}

//Display accommadation informations
void view_accom_info()
{
    printf("===================== Accommodations List =====================\n");
    int rooms_per_row = 4;
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        printf("Room %s: %s\t", room_Info[i].room_number, room_Info[i].room_status);

        if ((i + 1) % rooms_per_row == 0)
        {
            printf("\n");
        }
    }

    if (MAX_ROOMS % rooms_per_row != 0)
    {
        printf("\n");
    }

    printf("===============================================================\n\n");
}

//Initialize variables of structures
void init() 
{
    for (int i = 0; i < MAX_ROOMS; i++) 
    {
        strcpy(room_Info[i].room_status, DEFAULT_STAT);
        strcpy(room_Info[i].room_number, index_to_room(i));
    }

    for (int j = 0; j < MAX_EPLYS; j++) 
    {
        strcpy(eply_Info[j].department, NONE);
        strcpy(eply_Info[j].name, NONE);
        strcpy(eply_Info[j].ID, NONE);
        strcpy(eply_Info[j].password, NONE);
    }

    for (int k = 0; k < MAX_CUSTOMERS; k++) 
    {
        strcpy(cus_Info[k].number, NONE);
        strcpy(cus_Info[k].name, NONE);
        strcpy(cus_Info[k].ID, NONE);
        strcpy(cus_Info[k].password, NONE);
        strcpy(cus_Info[k].room_number, NONE);
        cus_Info[k].bill = 0;
    }
}

//Check if the input is valid when an integer is required
int int_input_check(int *input)
{
    if (scanf("%d", input) != 1)
    {
        printf("[ERROR] Invalid input,please try again!\n");

        while (getchar() != '\n');
        return 0;
    }
    else
    {
        return 1;
    }
}

//Find the index of ID by indentity
int find_ID(char *identity, char *ID)
{
    if (strcmp(identity, "Employee") == 0)
    {
        for (int i = 0; i < MAX_EPLYS; i++)
        {
            if (strcmp(eply_Info[i].ID, ID) == 0)
            {
                return i;
            }
        }
    }
    else if (strcmp(identity, "Customer") == 0)
    {
        for (int i = 0; i < MAX_CUSTOMERS; i++)
        {
            if (strcmp(cus_Info[i].ID, ID) == 0)
            {
                return i;
            }
        }
    }
    return -1;
}

//Check if the room number is valid
int valid_room_check(char *room)
{
    char prefix;
    char valid[FLOORS] = VALID_PREFIX;
    int number;
    
    if (strlen(room) != 3) return 0; 

    if (!isdigit(room[1]) || !isdigit(room[2])) return 0; 

    prefix = room[0];
    sscanf(&room[1], "%d", &number); 

    if (number < 1 || number > 50) return 0; 

    for (int i = 0; i < FLOORS; i++)
    {   
        if (valid[i] == prefix) return 1; 
    }

    return 0;
}

//Unified login behavior customized for different identities
int login(char *identity, char *ID)
{
    char pwd[MAX_PWD_LEN];

    while (1)
    {
        printf("[INPUT] Please enter your %s ID >> ", identity);
        scanf(" %[^\n]", ID);

        printf("[INPUT] Please enter your password >> ");
        scanf(" %[^\n]", pwd);

        if (strcmp(identity, "Admin") == 0)
        {
            if (strcmp(ID, ADMIN_ID) == 0)
            {
                if (strcmp(pwd, ADMIN_PWD) == 0)
                {
                    printf("[INFO] Welcome, Administrator.\n");
                    return 1;
                }
                else
                {
                    printf("[ERROR] Wrong password. Please try again!\n");
                    return 0;
                }
            }
        }
        else if (strcmp(identity, "Employee") == 0 || strcmp(identity, "Customer") == 0)
        {
            int pos = find_ID(identity, ID);

            if (pos != -1)
            {
                if (strcmp(identity, "Employee") == 0)
                {
                    if (strcmp(pwd, eply_Info[pos].password) == 0)
                    {
                        printf("[INFO] Welcome, %s: %s.\n", identity, eply_Info[pos].name);
                        return 1;
                    }
                }
                else
                {
                    if (strcmp(pwd, cus_Info[pos].password) == 0)
                    {
                        printf("[INFO] Welcome, %s: %s.\n", identity, cus_Info[pos].name);
                        return 1;
                    }
                }
                printf("[ERROR] Wrong password. Please try again!\n");
                return 0;
            }
        }
        printf("[ERROR] Unknown %s ID. Please try again!\n", identity);
        return 0;
    }
}

//Check password strength
int pwd_check(char *pwd)
{
    int length = strlen(pwd);
    int hasLetter = 0;
    int hasDigit = 0;

    if (length < 8)
        return 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(pwd[i]))
        {
            hasLetter = 1;
        }

        if (isdigit(pwd[i]))
        {
            hasDigit = 1;
        }
    }
    return hasLetter && hasDigit;
}

//Check if the phone number is consist of digits
int phone_number_check(char *number) {
    for (int j = 0; j < strlen(number); j++) {
        if (!isdigit(number[j])) {
            return 0;
        }
    }

    return 1;
}

//Check if the customer ID already exists.
int cus_ID_check(char *ID) {
    if (find_ID("Customer", ID) == -1) return 1;
    return 0;
}

//Limit the number of input attempts
int input_attempts(char *prompts, char *error, char *inputs, check_func func) {
    int attempts = 0;

    while (attempts < 3) {
        printf("%s", prompts);
        scanf(" %[^\n]", inputs);

        if (func(inputs)) {
            break;
        } else {
            printf("%s", error);
            attempts++;
        }
    }

    return attempts;
}