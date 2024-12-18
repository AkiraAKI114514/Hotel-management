#include "tools.h"


void admin(){
    char ID[MAX_ID_LEN];
    char password[MAX_PWD_LEN];
    int choice;
    while(login("Admin", ID) == 1){
        adminHelpMsg();
        if(int_input_check(&choice) != 1){
            printf("[ERROR] Invaild input, please try again.");
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
                            break;
                        }
                    }
                }

                continue;
                break;
            case 2://View customers' info
                for (int i = 0; i < MAX_ROOMS;i++){
                    if(strcmp(cus_Info[i].room_status,DEFAULT_STAT) != 0){
                        char temp_name[MAX_NAME_LEN], temp_ID[MAX_ID_LEN], temp_stat[10], temp_roomnum[4];
                        int temp_number = cus_Info[i].number, temp_bill = cus_Info[i].bill;
                        strcpy(temp_name, cus_Info[i].name);
                        strcpy(temp_ID, cus_Info[i].ID);
                        strcpy(temp_stat, cus_Info[i].room_status);
                        strcpy(temp_roomnum, cus_Info[i].room_number);
                        printf("--[Customers' Infomtion]--\n");
                        printf("=========================\n");
                        printf("| ID:\t%s\n",temp_ID);
                        printf("| Name:\t%s\n", temp_name);
                        printf("| Phone Number:\t%d\n", temp_number);
                        printf("| Room:\t%s (%s)\n", temp_roomnum,temp_stat);
                        printf("| Bill:\t%d\n", temp_bill);
                        printf("=========================\n\n");
                    }
                }
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
    return;
}
