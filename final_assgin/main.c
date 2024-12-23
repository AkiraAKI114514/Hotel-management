#include "admin_employee.h"

int main() {
    int choice;
    init();
    welcomeMsg();

    while (1) {
        menuHelpMsg();
        
        if (int_input_check(&choice)) {   
            switch (choice) {
                case 1:    
                    admin();
                    break;
                case 2:     
                    employee();
                    break;
                case 3:
                    //customer();
                    break;
                case 4:    
                    printf("[INFO] Exiting sytstem. Goodbye!\n");
                    return 0;
                default:  
                    printf("[ERROR] Invalid option,please try again!\n");
            }
        }
    }

    return 0;
}
