#include "tools.h"


void admin(){
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
    int choice;
    while(login("Admin", ID) == 1){
        adminHelpMsg();
        if(int_input_check(&choice) != 1){
            printf("[ERROR] Invaild input, please try again.\n");
            continue;
        }else{
            switch (choice)
            {
            case 1://record info
                while(1){
                    char *temp_num;
                    int temp_choice, temp_index;
                    printf("[INPUT] Enter the room number\n");
                    scanf("%s", &temp_num);
                    temp_index = room_to_index(temp_num);
                    RoomstatMsg();
                    if(int_input_check(&temp_choice) != 1){
                        printf("[ERROR] Invaild input, please try again.\n");
                        continue;
                    }else{
                        switch (temp_choice)
                        {
                        case 1:
                            strcpy(cus_Info[temp_index].room_status, DEFAULT_STAT);
                            break;

                        case 2:
                            strcpy(cus_Info[temp_index].room_status, BOOKED_STAT);
                            break;

                        case 3:
                            strcpy(cus_Info[temp_index].room_status, LIVEIN_STAT);
                            break;

                        default:
                            printf("[ERROR] Invaild input, please try again.\n");
                        }
                    }
                    break;
                }

                continue;
                break;
            case 2://View customers' info
                view_cus_info();
                continue;
                break;
            case 3:
                printf("[INFO] Returning to main menu.\n");
                return;
                break;
            default:
                printf("[ERROR] Invaild input, please try again.");
            }
        }
        break;
    }
    return;
}


void employee(){
    while(1){
        int choice1, choice2,eply_num;
        char temp_name[MAX_NAME_LEN], temp_dep[100], temp_pwd[MAX_PWD_LEN], temp_id[MAX_ID_LEN];
        EmployHelpMsg1();
        if(int_input_check(&choice1) != 1){
            printf("[ERROR] Invaild input, please try again.\n");
            continue;
        }else{
            switch (choice1)
            {
            case 1://Register by Department
                for (int j = 0; j < MAX_EPLY_NUMBER;j++){
                    if(strcmp(eply_Info[j].department,"NONE")==0){
                        eply_num = j;
                        break;
                    }
                }
                printf("[INPUT] Please enter your name >>");
                scanf("%s", &temp_name);
                printf("[INPUT] Please enter your password >>");
                scanf("%S", &temp_pwd);
                DepartmentMsg();
                while(1){
                    if(int_input_check(&choice2)!=1){
                        printf("[ERROR] Invaild input, please try again.\n");
                        continue;
                    }else{
                        switch (1)
                        {
                        case 1:
                            strcpy(eply_Info[eply_num].department, "Manangement");
                            strcpy(temp_dep, "M");
                            break;
                        case 2:
                            strcpy(eply_Info[eply_num].department, "Accounting");
                            strcpy(temp_dep, "A");
                            break;
                        case 3:
                            strcpy(eply_Info[eply_num].department, "Service");
                            strcpy(temp_dep, "S");
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                }

                strcpy(eply_Info[eply_num].name, temp_name);
                strcpy(eply_Info[eply_num].password, temp_pwd);
                sprintf(temp_id, "%d", eply_num);
                strcat(temp_id, temp_name);
                strcat(temp_id, temp_dep);
                strcpy(eply_Info[eply_num].ID, temp_id);
                printf("[INFO] Register Successed.\n");
                printf("Please check your infomation.\n");
                printf("=================================\n");
                printf("ID:\t%s\n", eply_Info[eply_num].ID);
                printf("Name:\t%s\n", eply_Info[eply_num].name);
                printf("Department:\t%s\n", eply_Info[eply_num].department);
                printf("=================================\n");
                break;

            case 2://login and view info
                while(1){
                    if(login("Employee",temp_id)!=1){
                        continue;
                    }else{
                        EmployHelpMsg2();
                        if(int_input_check(&choice2) == 0){
                            printf("[ERROR] Invaild input, please try again.\n");
                            continue;
                        }else{
                            switch (choice2)
                            {
                            case 1://View Customers
                                printf("--[Customers' Infomtion]--\n");
                                for (int i = 0; i < MAX_ROOMS; i++)
                                {
                                    view_cus_info();
                                }
                                break;
                            case 2://view accomodations list
                                printf("--[Accomodation list]--\n");
                                for (int i = 0; i < MAX_ROOMS;i++){
                                    char room_num[4];
                                    char temp_stat[10];
                                    strcpy(temp_stat, cus_Info[i].room_status);
                                    strcpy(room_num, cus_Info[i].room_number);
                                    printf("=================\n");
                                    printf("|%s:\t%s\n", room_num, temp_stat);
                                    printf("=================\n");
                                }
                                break;

                            default:
                                break;
                            }
                        }
                    }
                    break;
                }


            default:
                break;
            }
            break;
        }
    }
} 
