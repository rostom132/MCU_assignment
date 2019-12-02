#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "driver.h"
#define _XTAL_FREQ 8000000

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