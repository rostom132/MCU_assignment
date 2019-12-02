
#include "pin_manager.h"
#include "time_manager.h"

int read_button_A(){
    first_read_A = second_read_A;
    second_read_A = BUTTON_INC;
    if (first_read_A == second_read_A){
        if(second_read_A == 0)return 1;
        else return 2;
    }
    return 0;
}
int read_button_B(){
    first_read_B = second_read_B;
    second_read_B = BUTTON_DEC;
    if (first_read_B == second_read_B){
        if(second_read_B == 0)return 1;
        else return 2;
    }
    return 0;
}
int read_all_button(int button_A, int button_B){
    if (button_A == 1) return 1;
    if (button_B == 1) return 2;
    return 3;
}
