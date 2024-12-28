#include "tools.h"

void admin(){
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
    char temp_room_number[4];
    int flag;
    int choice_1;
    int choice_2;
    int temp_index;

    if (login("Admin", ID)) {
        while (1) {
            AdminHelpMsg();

            if (int_input_check(&choice_1)) {
                switch (choice_1) {
                    //Record infomations
                    case 1:
                        flag = 1;

                        while (flag) {
                            printf("[INFO] Room number format: Floor(G,1,2,3) + Number(1-50)\n");
                            printf("[INPUT] Enter the room number >> ");
                            scanf(" %[^\n]", temp_room_number);

                            if (!valid_room_check(temp_room_number)) {
                                printf("[ERROR] Invalid room number. Please try again!\n");
                                break;
                            }

                            temp_index = room_to_index(temp_room_number);
                            RoomStatMsg();

                            if (int_input_check(&choice_2)) {
                                switch (choice_2) {
                                    case 1:
                                        strcpy(room_Info[temp_index].room_status, DEFAULT_STAT);
                                        printf("[INFO] The status of room %s has been changed to \"%s\".\n", temp_room_number, DEFAULT_STAT);
                                        flag = 0;
                                        break;
                                    case 2:
                                        strcpy(room_Info[temp_index].room_status, BOOKED_STAT);
                                        printf("[INFO] The status of room %s has been changed to \"%s\".\n", temp_room_number, BOOKED_STAT);
                                        flag = 0;
                                        break;
                                    case 3:
                                        strcpy(room_Info[temp_index].room_status, LIVEIN_STAT);
                                        printf("[INFO] The status of room %s has been changed to \"%s\".\n", temp_room_number, LIVEIN_STAT);
                                        flag = 0;
                                        break;
                                    default:
                                        printf("[ERROR] Invalid option. Please try again!\n");
                                        continue;
                                }
                            }
                        }
                        break;
                    //View customers' infomations
                    case 2:
                        view_cus_info();
                        break;
                    case 3:
                        printf("[INFO] Returning to main menu.\n");
                        return;
                    default:
                        printf("[ERROR] Invaild option. Please try again!\n");
                }
            }
        }
    }
}


void employee() {
    int choice_1;
    int choice_2;
    int choice_3; 
    int eply_num = -1;
    int register_flag;
    int login_flag;
    int attempts;
    char ID[MAX_ID_LEN];
    char temp_pwd[MAX_PWD_LEN];

    while (1) {
        EmployHelpMsg1();

        if (int_input_check(&choice_1)) {
            switch (choice_1) {
                //Register by Department
                case 1: 
                    eply_num = -1;

                    for (int j = 0; j < MAX_EPLYS; j++) {
                        if (strcmp(eply_Info[j].department, NONE) == 0) {
                            eply_num = j;
                            break;
                        }
                    }

                    if (eply_num == -1) {
                        printf("[ERROR] No available slots for new employees!\n");
                        break;
                    }

                    printf("[INPUT] Please enter your name >> ");
                    scanf(" %[^\n]", eply_Info[eply_num].name);

                    attempts = input_attempts(
                        "[INPUT] Please enter your password(length > 8, must include both number and characters) >> ",
                        "[ERROR] Invalid password. Please try again!\n",
                        temp_pwd,
                        pwd_check
                    );

                    if (attempts == 3) {
                        printf("[ERROR] Too many failed attempts. Returning to main menu!\n");
                        continue;
                    }

                    DepartmentMsg();
                    printf("[INPUT] Please choose your department >> ");

                    register_flag = 1;

                    while (register_flag) {
                        if (int_input_check(&choice_2)) {
                            switch (choice_2) {
                                case 1:
                                    strcpy(eply_Info[eply_num].department, "Management");
                                    sprintf(eply_Info[eply_num].ID, "MNG%02d", eply_num + 1);
                                    register_flag = 0;
                                    break;
                                case 2:
                                    strcpy(eply_Info[eply_num].department, "Accounting");
                                    sprintf(eply_Info[eply_num].ID, "ACC%02d", eply_num + 1);
                                    register_flag = 0;
                                    break;
                                case 3:
                                    strcpy(eply_Info[eply_num].department, "Service");
                                    sprintf(eply_Info[eply_num].ID, "SVC%02d", eply_num + 1);
                                    register_flag = 0;
                                    break;
                                default:
                                    printf("[ERROR] Invalid option. Please try again!\n");
                                    continue;
                            }
                        }
                    }

                    printf("[INFO] Registration Successful!\n");
                    printf("=================================\n");
                    printf("Employee ID   : %s\n", eply_Info[eply_num].ID);
                    printf("Name          : %s\n", eply_Info[eply_num].name);
                    printf("Department    : %s\n", eply_Info[eply_num].department);
                    printf("=================================\n");
                    break;

                //Login
                case 2:
                    if (login("Employee", ID)) {
                        login_flag = 1;
                        
                        while (login_flag) {
                            EmployHelpMsg2();

                            if (int_input_check(&choice_3)) {
                                switch (choice_3) {
                                    //View customers' informations
                                    case 1: 
                                        view_cus_info();
                                        break;
                                    //View accommodation list   
                                    case 2: 
                                        view_accom_info();
                                        break;
                                    case 3:
                                        printf("[INFO] Returning to previous menu.\n");
                                        login_flag = 0;
                                        break;
                                    default:
                                        printf("[ERROR] Invalid option. Please try again!\n");
                                        continue;
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    printf("[INFO] Returning to main menu.\n");
                    return;
                default:
                    printf("[ERROR] Invalid option. Please try again!\n");
                    continue;
            }
        }
    }
}

void customer() {
    int choice_1;
    int choice_2;
    int cus_num = -1;
    int attempts;
    int login_flag;
    int room_index;
    char ID[MAX_ID_LEN];
    char temp_pwd[MAX_PWD_LEN];
    char temp_ID[MAX_ID_LEN];
    char temp_room_number[4];
    char temp_number[MAX_NUMBER_LEN];

    while (1) {
        CusHelpMsg1();

        if (int_input_check(&choice_1)) {
            switch (choice_1) {
                case 1:
                    cus_num = -1;

                    for (int i = 0; i < MAX_EPLYS; i++) {
                        if (strcmp(cus_Info[i].ID, NONE) == 0) {
                            cus_num = i;
                            break;
                        }
                    }

                    if (cus_num == -1) {
                        printf("[ERROR] No available slots for new customers!\n");
                        break;
                    }

                    printf("[INPUT] Please enter your name >> ");
                    scanf(" %[^\n]", cus_Info[cus_num].name);

                    attempts = input_attempts(
                        "[INPUT] Please enter you ID >> ",
                        "[ERROR] This ID has already exists. Please try again!\n",
                        temp_ID,
                        cus_ID_check
                    );
                    
                    if (attempts == 3) {
                        printf("[ERROR] Too many failed attempts. Returning to main menu!\n");
                        break;
                    }
 
                    attempts = input_attempts(
                        "[INPUT] Please enter you phone number(all digits) >> ",
                        "[ERROR] Invalid phone number. Please try again!\n",
                        temp_number,
                        phone_number_check
                    );

                    if (attempts == 3) {
                        printf("[ERROR] Too many failed attempts. Returning to main menu!\n");
                        break;
                    }

                    attempts = input_attempts(
                        "[INPUT] Please enter your password(length > 8, must include both number and characters) >> ",
                        "[ERROR] Invalid password. Please try again!\n",
                        temp_pwd,
                        pwd_check
                    );

                    if (attempts == 3) {
                        printf("[ERROR] Too many failed attempts. Returning to main menu!\n");
                        break;
                    }

                    strcpy(cus_Info[cus_num].ID, temp_ID);
                    strcpy(cus_Info[cus_num].number, temp_number);
                    strcpy(cus_Info[cus_num].password, temp_pwd);

                    printf("[INFO] Registration Successful!\n");
                    printf("=================================\n");
                    printf("Customer ID   : %s\n", cus_Info[cus_num].ID);
                    printf("Name          : %s\n", cus_Info[cus_num].name);
                    printf("Phone number  : %s\n", cus_Info[cus_num].number);
                    printf("Room number   : %s\n", cus_Info[cus_num].room_number);
                    printf("Bill          : %.2f\n", cus_Info[cus_num].bill);
                    printf("=================================\n");
                    break;
                case 2:
                    if (login("Customer", ID)) {
                        cus_num = find_ID("Customer", ID);
                        login_flag = 1;

                        while (login_flag) {
                            CusHelpMsg2();

                            if (int_input_check(&choice_2)) {
                                switch (choice_2) {
                                    case 1:
                                        printf("====== Accommodation Informations ======\n");
                                        printf("Customer ID   : %s\n", cus_Info[cus_num].ID);
                                        printf("Name          : %s\n", cus_Info[cus_num].name);
                                        printf("Phone Number  : %s\n", cus_Info[cus_num].number);

                                        if (strcmp(cus_Info[cus_num].room_number, NONE) == 0)
                                        {
                                            printf("Room Number   : %s\n", NONE);
                                        }
                                        else
                                        {   
                                            room_index = room_to_index(cus_Info[cus_num].room_number);
                                            printf("Room Number   : %s (%s)\n", cus_Info[cus_num].room_number, room_Info[room_index].room_status);

                                        }
                                        
                                        printf("Bill          : %.2f\n", cus_Info[cus_num].bill);
                                        printf("========================================\n");
                                        break;
                                    case 2:
                                        if (strcmp(cus_Info[cus_num].room_number, NONE) != 0) {
                                            printf("[ERROR] You have already booked a room!\n");
                                            break;
                                        }

                                        find_empty_rooms();
                                        printf("[INPUT] Please enter the room number >> ");
                                        scanf(" %[^\n]", temp_room_number);

                                        if (!valid_room_check(temp_room_number)) {
                                            printf("[ERROR] Invalid room number. Please try again!\n");
                                            break;
                                        }

                                        room_index = room_to_index(temp_room_number);

                                        if (strcmp(room_Info[room_index].room_status, DEFAULT_STAT) != 0) {
                                            printf("[ERROR] The room:%s is unavailable. Please try again!\n", temp_room_number);
                                            break;
                                        }
                                        
                                        printf("[INFO] Book Successful!\n");

                                        strcpy(cus_Info[cus_num].room_number, temp_room_number);
                                        strcpy(room_Info[room_index].room_status, BOOKED_STAT);
                                        cus_Info[cus_num].bill += ROOM_PRICE;

                                        printf("=================================\n");
                                        printf("Room number   : %s\n", cus_Info[cus_num].room_number);
                                        printf("Bill          : %.2f\n", cus_Info[cus_num].bill);
                                        printf("=================================\n");
                                        break;
                                    case 3:
                                        printf("====== Bill Information ======\n");
                                        printf("Bill    : %.2f\n", cus_Info[cus_num].bill);
                                        printf("==============================\n");
                                        break;
                                    case 4:
                                        printf("[INFO] Returning to previous menu.\n");
                                        login_flag = 0;
                                        break;
                                    default:
                                        printf("[ERROR] Invalid option. Please try again!\n");
                                        continue;
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    printf("[INFO] Returning to main menu.\n");
                    return;
                default:
                    printf("[ERROR] Invalid option. Please try again!\n");
                    continue;
            }
        }
    }
}