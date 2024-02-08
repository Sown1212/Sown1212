#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 20e6
#define RS RC0
#define RW RC1
#define E RC2

float adc;
int temperature;
char a, b, c, d, e, f, g;

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
    unsigned char arr_1[] = "ADC Value:";
    for(i = 0; i < 11; i++){
         lcd_char(arr_1[i]);
    }
    lcd_cmd(0xC0);
    unsigned char arr_2[] = "Temperature:";
    for(i = 0; i < 13; i++){
         lcd_char(arr_2[i]);
    }
}

void __interrupt(high_priority) Change_ADC(){
    if(ADIF == 1){
        ADIF = 0;
        adc = ADRESH << 8;
        adc = adc + ADRESL;
    }
}

void set_lcd(){
    TRISB = 0;
    TRISC = 0;
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
}

void set_adc(){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    ADCON0 = 0x41;
    ADCON1 = 0x8E;
    TRISAbits.TRISA0 = 1;
}

void read_temper(){
    float adc1 = adc*((float)4.887);
    adc1 = adc1/10;
    temperature = (int)adc1;
    c = temperature % 10;
    temperature /= 10;
    b = temperature % 10;
    temperature /= 10;
    a = temperature % 10;
    lcd_cmd(0xCD);
    lcd_char(a+0x30);
    lcd_char(b+0x30);
    lcd_char(c+0x30);
}

void read_adc(){
    int ADC = (int)adc;
    g = ADC % 10;
    ADC /= 10;
    f = ADC % 10;
    ADC /= 10;
    e = ADC % 10;
    ADC /= 10;
    d = (char)ADC;
    lcd_cmd(0x8B);
    lcd_char(d+0x30);
    lcd_char(e+0x30);
    lcd_char(f+0x30);
    lcd_char(g+0x30);
}

void main(){
    set_lcd();
    set_adc();
    lcd_display();
    while(1){
        ADCON0 = ADCON0|0x04;
        read_adc();
        read_temper();
    }
}