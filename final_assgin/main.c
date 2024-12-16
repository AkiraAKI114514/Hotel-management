#include <stdio.h>

int main() {
    int choice;

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
                    customer();
                    break;
                case 4:    
                    printf("[INFO] Exiting sytstem. Goodbye!\n");
                    return 0;
                default:  
                    printf("[ERROR] Invalid input. Please try again!\n");
            }
        }
    }

    return 0;
}
