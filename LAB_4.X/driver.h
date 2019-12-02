#ifndef _DRIVER_H_

#define _DRIVER_H_

#include <stdint.h>

#define NUMBER_TASK 10

typedef unsigned int timestamp_t;
typedef void (*timer_callback_t)();
typedef unsigned long long int uint64_t;

void start_timer(int time_vadd);
timestamp_t get_time(void);
uint32_t register_timer(uint64_t delay,uint64_t period,timer_callback_t callback, void *data );
int remove_timer(uint32_t id);
int stop_timer(void);
int timer_ISR();

void dispatch(void);
void add_tasks(int id);

//Register

#endif