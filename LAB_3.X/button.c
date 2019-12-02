
#include "pin_manager.h"
#include "variables.h"

int read_button_change(){
    first_read_change = second_read_change;
    second_read_change = BUTTON_CHANGE;
    if (first_read_change == second_read_change){
        if(second_read_change == 0)return 1;
        else return 2;
    }
    return 0;
}
int read_button_sel(){
    first_read_sel = second_read_sel;
    second_read_sel = BUTTON_SEL;
    if (first_read_sel == second_read_sel){
        if(second_read_sel == 0)return 1;
        else return 2;
    }
    return 0;
}
int read_all_button(int button_A, int button_B){
    if (button_A == 1) return 1;
    if (button_B == 1) return 2;
    return 3;
}
