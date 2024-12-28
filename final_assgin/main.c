#include "admin_employee_customer.h"

int main() {
    int choice;
    init();
    WelcomeMsg();

    while (1) {
        MenuHelpMsg();
        
        if (int_input_check(&choice)) {   
            switch (choice) {
                case 1:    
                    admin();
                    break;
                case 2:     
                    employee();
                    break;
                case 3:
                    customer();
                    break;
                case 4:    
                    printf("[INFO] Exiting sytstem. Goodbye!\n");
                    return 0;
                default:  
                    printf("[ERROR] Invalid option. Please try again!\n");
                    continue;
            }
        }
    }

    return 0;
}