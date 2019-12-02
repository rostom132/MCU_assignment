#ifndef CLOCK_H
#define CLOCK_H

//display.c
void initial_display();                                             //Initial display of clock in every state
void display_clock(int type_display, int state_display);            //display Hour, Minute, Second on LCD
void blink(int state, int type);                                    //support for function display_change_state
void display_change_state(void);                                    //display LCD everytime the state of machine changed

//clock.c
void clock_count(int state);
void change_time(void);
void stop_watch_count(void);                                    

#endif