/*
 * File:   driver.c
 * Author: Dell
 *
 * Created on October 5, 2019, 11:25 AM
 */


#include <xc.h>
#include "pin_manager.h"
#include "driver.h"
#include "variables.h"
#include "register.h"

void start_timer(int type){
    
    enum Timer_type time_vaddr = type;
    switch(time_vaddr){
        case TIMER_TMR0:
            T0CON = 0b11000111;
            TMR0 = 0xB2;
//            T0CON = T0CON_SETTING;
            INTCONbits.TMR0IE = 1;
            INTCONbits.TMR0IF = 0;
//            TMR0L = 0xFFFF -  TIME_INTERUPT;
//            TMR0H = (0xFFFF - TIME_INTERUPT)>>8;
            break;
        case TIMER_TMR1:
            T1CON = 0x0F;
            TMR1H = 0x80; 
            TMR1L = 0x00;
            PIR1bits.TMR1IF = 0;
            PIE1bits.TMR1IE = 1;
            T1CONbits.TMR1ON = 1;
            break;
        case TIMER_TMR2:
            break;
        case TIMER_TMR3:
            break;
        case TIMER_TMR4:
            break;
    }
    ALLOW_TIMER_REGISTER = 1;
    return;
}

timestamp_t get_time(void){
    return time;
}

uint32_t register_timer(uint64_t delay,uint64_t period,timer_callback_t callback, void *data ){
    if (NUMBER_EXIST_TASKS >= NUMBER_TASK ) return 0;
    NUMBER_EXIST_TASKS ++;
    int i =0;
    while(1){
        if (tasks[i].period == 0) {
            NUMBER_EXIST = i;
            break;
        }
        i++;
    }
    tasks[NUMBER_EXIST].callback = callback;
    tasks[NUMBER_EXIST].data = data;
    tasks[NUMBER_EXIST].period = period;
    if (NUMBER_EXIST == 0){
        tasks[NUMBER_EXIST].next = -1;
        HEAD_QUEUE = 0;
        tasks[NUMBER_EXIST].delay = delay;
        return NUMBER_EXIST;
    }
    unsigned int temp;
    if (tasks[HEAD_QUEUE].delay >= delay){
        tasks[NUMBER_EXIST].next = HEAD_QUEUE;
        tasks[HEAD_QUEUE].delay = tasks[HEAD_QUEUE].delay - delay;
        tasks[NUMBER_EXIST].delay = delay;
        HEAD_QUEUE = NUMBER_EXIST;
        return NUMBER_EXIST;
    }
    
    int temp_index = HEAD_QUEUE;
    unsigned long long int temp_delay = tasks[HEAD_QUEUE].delay;
    while(1){
        if (tasks[temp_index].next == -1){
            tasks[temp_index].next = NUMBER_EXIST;
            tasks[NUMBER_EXIST].next = -1;
            tasks[NUMBER_EXIST].delay = delay - temp_delay;
            return NUMBER_EXIST;
        }
        temp_delay = temp_delay + tasks[tasks[temp_index].next].delay;
        if (temp_delay >= delay){
            temp_delay = temp_delay - tasks[tasks[temp_index].next].delay;
            tasks[NUMBER_EXIST].delay = delay - temp_delay; 
            tasks[NUMBER_EXIST].next = tasks[temp_index].next;
            tasks[tasks[NUMBER_EXIST].next].delay = tasks[tasks[NUMBER_EXIST].next].delay - tasks[NUMBER_EXIST].delay;
            tasks[temp_index].next = NUMBER_EXIST;
            return NUMBER_EXIST;
        }
        temp_index = tasks[temp_index].next;
    }
    return NUMBER_EXIST;
}
int remove_timer (uint32_t id){
    if (id == HEAD_QUEUE){
        tasks[HEAD_QUEUE].callback = NULL;
        tasks[HEAD_QUEUE].period = 0;
        tasks[tasks[HEAD_QUEUE].next].delay +=  tasks[HEAD_QUEUE].delay; 
        tasks[HEAD_QUEUE].delay = 0;
        tasks[HEAD_QUEUE].data = NULL;
        HEAD_QUEUE = tasks[HEAD_QUEUE].next;
        tasks[HEAD_QUEUE].next = -1;
        NUMBER_EXIST_TASKS --;
        return id;
    }
    int temp_index = HEAD_QUEUE;
    while(1){
        if (tasks[temp_index].next == id){
            tasks[id].callback = NULL;
            tasks[id].period = 0;
            tasks[tasks[id].next].delay += tasks[id].delay; 
            tasks[id].delay = 0;
            tasks[id].data = NULL;
            tasks[temp_index].next = tasks[id].next;
            tasks[id].next = -1;
            NUMBER_EXIST_TASKS --;
            return id;
        }
        temp_index = tasks[temp_index].next;
        if (temp_index == -1) return -1;
    }
}

int stop_timer(void){
    INTCONbits.TMR0IE = 0;
    PIE1bits.TMR1IE = 0;
    return 1;
}

int timer_ISR(){
    int i = 0;
    while (execution[i] != 0) i++;
    if (tasks[HEAD_QUEUE].delay > 0) tasks[HEAD_QUEUE].delay -= 10;
    while (tasks[HEAD_QUEUE].delay == 0) { 
        int temp = HEAD_QUEUE;
        HEAD_QUEUE = tasks[HEAD_QUEUE].next;
        execution[i] = temp+1;
        add_tasks(temp); 
        i = i + 1;
    }
    return 1;
}
void dispatch(void){ 
    int i = 0;
    while(execution[i] > 0){
        (tasks[execution[i]-1].callback)(tasks[execution[i]-1].data);
        if (execution[i] == 1) remove_tasks ++;
        execution[i] = 0;
        i = i + 1; 
    }
}

void add_tasks(int id){
    int temp_next = HEAD_QUEUE;
    if (tasks[temp_next].delay >= tasks[id].period){
        tasks[id].next = temp_next;
        tasks[id].delay = tasks[id].period;
        tasks[temp_next].delay =tasks[temp_next].delay - tasks[id].delay; 
        HEAD_QUEUE = id;
        return;
    }
    unsigned long long int temp_delay = tasks[HEAD_QUEUE].delay;
    while(1){
        if (tasks[temp_next].next == -1){
            tasks[temp_next].next = id;
            tasks[id].next = -1;
            tasks[id].delay = tasks[id].period - temp_delay;
            return;
        }
        temp_delay = temp_delay + tasks[tasks[temp_next].next].delay;
        if (temp_delay >= tasks[id].period) {
            temp_delay = temp_delay -tasks[tasks[temp_next].next].delay;
            tasks[id].delay = tasks[id].period - temp_delay;
            tasks[id].next = tasks[temp_next].next;
            tasks[temp_next].next = id;
            tasks[tasks[id].next].delay = tasks[tasks[id].next].delay - tasks[id].delay;
            return;
        }
        temp_next = tasks[temp_next].next;
    }
}