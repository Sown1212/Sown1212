
/*
 * File:   Mplab.c
 * Author: Admin
 *
 * Created on Ng�y 21 th�ng 1 n?m 2024, 13:09
 */
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 20e6

unsigned short time_count = 0;
void __interrupt(high_priority) count(){
    if(INTCONbits.TMR0IF == 1){
        INTCONbits.TMR0IF = 0;
        time_count++;
    }
    if(time_count == 76)
        PORTB = 0xFF;
    if(time_count == 152){
        PORTB = 0x00;
        time_count = 0;
    }
}

void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
    OPTION_REG = 0x07;
    TRISB = 0;
    PORTB = 0x00;
    while(1){
    }
    return;
}