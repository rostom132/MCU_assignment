#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>

#ifdef _18F8722 
#pragma config  OSC = INTIO7
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#define OSCCON_SETTING 0b00100111                // OSCON values 250kHz
#define T0CON_SETTING 0b11000101                 // prescale = 64
#define COEFFECIENT 0.997                        // multi

#define LED_DISPLAY_DIR                     TRISD           //direction of LED
#define LED_DISPLAY_INIT                    PORTD
#define LED_DISPLAY                         LATD                //display the result
#define BUTTON_INC_DIR                      TRISAbits.RA5    //direction of button increase
#define BUTTON_INC                          PORTAbits.RA5        //the button used for increasing
#define BUTTON_DEC_DIR                      TRISBbits.RB0    //direction of button decrease
#define BUTTON_DEC                          PORTBbits.RB0        //the button used for decreasing

//--------------------------variables---------------------------//
typedef unsigned char uint8_t;
uint8_t first_read_A = 1;
unsigned char second_read_A = 1;
unsigned char first_read_B = 1;
unsigned char second_read_B = 1;

//--------------------------------------------------------------//

void initial(void);
int read_button_A();
int read_button_B();
int read_all_button(int button_A, int button_B);
#endif