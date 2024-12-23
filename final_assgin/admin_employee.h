#include "tools.h"

void admin(){
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
    char temp_num[4];
    int flag = 1;
    int choice_1;
    int choice_2;
    int temp_index;

    if (login("Admin", ID)) {
        while (1) {
            adminHelpMsg();

            if (int_input_check(&choice_1)) {
                switch (choice_1) {
                    case 1://record info
                        flag = 1;
                        while (flag) {
                            printf("[INPUT] Enter the room number >> ");
                            scanf("%s", temp_num);

                            if (valid_room_check(temp_num) != 1) {
                                printf("[ERROR] Invalid room number,please try again!\n");
                                continue;
                            }

                            temp_index = room_to_index(temp_num);
                            RoomstatMsg();

                            if (int_input_check(&choice_2)) {
                                switch (choice_2) {
                                    case 1:
                                        strcpy(room_Info[temp_index].room_status, DEFAULT_STAT);
                                        printf("[INFO] The status of room %s has been changed to \"%s\".\n", temp_num, DEFAULT_STAT);
                                        flag = 0;
                                        break;
                                    case 2:
                                        strcpy(room_Info[temp_index].room_status, BOOKED_STAT);
                                        printf("[INFO] The status of room %s has been changed to \"%s\".\n", temp_num, BOOKED_STAT);
                                        flag = 0;
                                        break;
                                    case 3:
                                        strcpy(room_Info[temp_index].room_status, LIVEIN_STAT);
                                        printf("[INFO] The status of room %s has been changed to \"%s\".\n", temp_num, LIVEIN_STAT);
                                        flag = 0;
                                        break;
                                    default:
                                        printf("[ERROR] Invaild option, please try again!\n");
                                }
                            }
                        }
                        break;
                    case 2://View customers' info
                        view_cus_info();
                        break;
                    case 3:
                        printf("[INFO] Returning to main menu.\n");
                        return;
                    default:
                        printf("[ERROR] Invaild option, please try again!\n");
                }
            }
        }
    }
}


void employee() {
    int choice1, choice2, choice3, eply_num = -1;
    int register_flag = 1;
    int login_flag = 1;
    char ID[MAX_ID_LEN];

    while (1) {
        EmployHelpMsg1();

        if (int_input_check(&choice1)) {
            switch (choice1) {
                case 1: // Register by Department
                    eply_num = -1;

                    for (int j = 0; j < MAX_EPLYS; j++) {
                        if (strcmp(eply_Info[j].department, "NONE") == 0) {
                            eply_num = j;
                            break;
                        }
                    }

                    if (eply_num == -1) {
                        printf("[ERROR] No available slots for new employees!\n");
                        break;
                    }

                    // Get employee info directly into the structure
                    printf("[INPUT] Please enter your name >> ");
                    scanf("%s", eply_Info[eply_num].name);
                    printf("[INPUT] Please enter your password >> ");
                    scanf("%s", eply_Info[eply_num].password);

                    DepartmentMsg();
                    printf("[INPUT] Please choose your department >> ");

                    register_flag = 1;
                    while (register_flag) {
                        if (int_input_check(&choice2)) {
                            switch (choice2) {
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
                                    printf("[ERROR] Invalid option,please try again!\n");
                            }
                        }
                    }

                    // Output registration information
                    printf("[INFO] Registration Successful!\n");
                    printf("=================================\n");
                    printf("Employee ID   : %s\n", eply_Info[eply_num].ID);
                    printf("Name          : %s\n", eply_Info[eply_num].name);
                    printf("Department    : %s\n", eply_Info[eply_num].department);
                    printf("=================================\n");
                    break;

                case 2:
                    if (login("Employee", ID)) {
                        login_flag = 1;
                        
                        while (login_flag) {
                            EmployHelpMsg2();

                            if (int_input_check(&choice3)) {
                                switch (choice3) {
                                    case 1: // View Customers
                                        view_cus_info();
                                        break;
                                    case 2: // View accommodation list
                                        view_accom_info();
                                        break;
                                    case 3:
                                        printf("[INFO] Returning to previous menu.\n");
                                        login_flag = 0;
                                        break;
                                    default:
                                        printf("[ERROR] Invalid option. Please try again!\n");
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
            }
        }
    }
}

