#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 20e6
#define RS RC0
#define RW RC1
#define E RC2
#define TX TRISCbits.TRISC6
#define RX TRISCbits.TRISC7

void lcd_char(unsigned char c){
    RS = 1;
    RW = 0;
    PORTB = (c & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
    PORTB = ((c<<4) & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
    RS = 0;
}

void lcd_cmd(unsigned char cmd){
    RS = 0;
    RW = 0;
    PORTB = (cmd & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
    PORTB = ((cmd<<4) & 0xF0);
    E = 1;
    __delay_ms(2);
    E = 0;
}

void lcd_display(){
    lcd_cmd(0x80);
    unsigned char i;
    unsigned char arr_1[] = "Serial Interrupt";
    for(i = 0; i < 16; i++){
         lcd_char(arr_1[i]);
    }
    lcd_cmd(0xC0);
    unsigned char arr_2[] = "KEY = ";
    for(i = 0; i < 6; i++){
         lcd_char(arr_2[i]);
    }
}

void tranmit(char c){
    TXREG = c;
    while(!TXIF);
    TXIF = 0;
}

unsigned char receive(){
    while(!RCIF);
    RCIF = 0;
    return RCREG;
 }

void set_lcd(){
    TRISB = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
}

void set_uart(){
    SPBRG = 32;
    TXEN = 1;
    SPEN = 1;
    CREN = 1;
    TX = 0;
    RX = 1;
}

void main(){
    set_lcd();
    set_uart();
    lcd_display();
    while(1){
        char c = 0;
        c = receive();
        if(c != 0){
            lcd_cmd(0xC6);
            lcd_char(c);
        }
    }
}