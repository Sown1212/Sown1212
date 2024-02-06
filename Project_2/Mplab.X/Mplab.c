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
#define LED1 RC1
#define LED2 RC2

unsigned char number = 0;
unsigned char seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

unsigned char time;
void __interrupt(high_priority) count(){
    if(INTCONbits.TMR0IF == 1){
        time++;
        INTCONbits.TMR0IF = 0;
    }
}

void display(){
    unsigned char num_LED1 = number/10;
    unsigned char num_LED2 = number%10;
    LED1 = 1;
    PORTB = seg[num_LED1];
    __delay_ms(5);
    LED1 = 0;
    LED2 = 1;
    PORTB = seg[num_LED2];
    __delay_ms(5);
    LED2 = 0;
}

void main(){
    TRISB = 0;
    TRISC = 0;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
    OPTION_REG = 0x07;
    while(1){
        TMR0 = 59;
        if(time == 100){
            number++;
            time = 0;
        }
        if(number == 100)
            number = 0;
        display();
    }
}
