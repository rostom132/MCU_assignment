#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "driver.h"

typedef unsigned char BYTE_1;

BYTE_1 first_read_A = 1;
BYTE_1 second_read_A = 0;
BYTE_1 first_read_B = 1;
BYTE_1 second_read_B = 0;
BYTE_1 button_A = 0;
BYTE_1 button_B = 0;
BYTE_1 BUTTON_STATE = 1;
BYTE_1 BUTTON_INC_STATE = 1;

BYTE_1 hold_but_B = 0;
BYTE_1 id_hold_but_B = 0;

int temp_heat_up = 0;
int temp_humidity = 0;

char TIME_SWAP = 1;
char TEMP_SWAP = 5;
char HUMI_SWAP = 50;

enum state {IDLE, HEAT_UP, WORKING, TIME_OUT, SETTING};
enum state state_machine;

enum state_work {HEATER_WORK, HEATPUMB_WORK};
enum state_work state_working;

enum state_setting { SET_TIME, SET_TEMP, SET_HUMI};
enum state_setting setting;

int time_checkout_HEATER = 0,
    time_checkout_HEATPUMB = 0;

int remove_tasks =0;
int NUMBER_EXIST = 0;
int NUMBER_EXIST_TASKS = 0;
int HEAD_QUEUE = 0;
unsigned char ALLOW_TIMER_REGISTER = 0;
unsigned long long int time = 0;

int HEAD_ARRAY = 0;
int count_count = 0;
int ledVal = 0;

typedef struct{    
    timer_callback_t callback;
    uint64_t delay;
    uint64_t period;
    void* data;
    int next;
} sTask;

int execution[NUMBER_TASK] = {0};
sTask tasks[NUMBER_TASK];

enum Timer_type {TIMER_TMR0, TIMER_TMR1, TIMER_TMR2, TIMER_TMR3, TIMER_TMR4};

#endif