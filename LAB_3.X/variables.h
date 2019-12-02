#ifndef VARIABLES_H
#define VARIABLES_H

typedef unsigned char BYTE_1;

enum state {MODE_0, MODE_1, MODE_2, MODE_3, MODE_4};
enum state state_machine;
enum state_button {NORMAL, PRESS, HOLD_1S};
enum state_button state_but_sel;

//CLOCK
BYTE_1 millis_system = 0;
BYTE_1 millis = 0;
BYTE_1 second = 0;
BYTE_1 minute = 0;
BYTE_1 hour = 0;

//STOP WATCH
BYTE_1 millis_stop_watch = 0;
BYTE_1 millis_10_stop = 0;
BYTE_1 second_stop = 0;
BYTE_1 minute_stop = 0;

//BUTTON
BYTE_1 first_read_change = 0;
BYTE_1 second_read_change = 0;
BYTE_1 first_read_sel = 0;
BYTE_1 second_read_sel = 0;
BYTE_1 init_setting = 0;
BYTE_1 button = 0;
BYTE_1 count_but = 0;
BYTE_1 count_sel = 0;

//BLINK
BYTE_1 blink_count = 0;
BYTE_1 blink_state = 0;

//FLAG
BYTE_1 minute_flag = 0;
BYTE_1 hour_flag = 0;
BYTE_1 button_flag = 3;
BYTE_1 stop_watch_flag = 0;
BYTE_1 second_stop_flag = 0;
BYTE_1 minute_stop_flag = 0;
BYTE_1 change_state = 0;

#endif