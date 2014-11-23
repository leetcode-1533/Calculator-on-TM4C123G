#include "lcd.h"
#include "timer.h"



void en_pulse(void){
	EN_1 = 0x02;
	us_delay(20);
	EN_1 = 0x00;
}

void lcd_init(void){

	int delay;

	SYSCTL_RCGC2_R |= 0x02;
	delay = 0;

	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xF3;
	GPIO_PORTB_AMSEL_R &= ~0xF3;
	GPIO_PORTB_AFSEL_R &= ~0xF3;
	GPIO_PORTB_PCTL_R &= ~0xFFFF00FF;
	GPIO_PORTB_DIR_R |= 0xF3;
	GPIO_PORTB_DEN_R |= 0xF3;

	ms_delay(15);

	RS_0 = 0;
	EN_1 = 0;

	GPIO_PORTB_DATA_R = 0x30;
	en_pulse();


	ms_delay(5);

	GPIO_PORTB_DATA_R = 0x30;
	en_pulse();

	us_delay(100);
//3
	GPIO_PORTB_DATA_R = 0x30;
	en_pulse();
	ms_delay(100);

	GPIO_PORTB_DATA_R = 0x20;
	en_pulse();
	ms_delay(100);

}

void lcd_eight_init(void){

	int delay;

	SYSCTL_RCGC2_R |= 0x06;
	delay = 0;

	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xF3;
	GPIO_PORTB_AMSEL_R &= ~0xF3;
	GPIO_PORTB_AFSEL_R &= ~0xF3;
	GPIO_PORTB_PCTL_R &= ~0xFFFF00FF;
	GPIO_PORTB_DIR_R |= 0xF3;
	GPIO_PORTB_DEN_R |= 0xF3;

	GPIO_PORTC_LOCK_R = 0x4C4F434B;
	GPIO_PORTC_CR_R |= 0xF0;
	GPIO_PORTC_AMSEL_R &= ~0xF0;
	GPIO_PORTC_AFSEL_R &= ~0xF0;
	GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
	GPIO_PORTC_DIR_R |= 0xF0;
	GPIO_PORTC_DEN_R |= 0xF0;

	ms_delay(15);
	//first
	GPIO_PORTB_DATA_R = 0x30;
	en_pulse();
	ms_delay(5);
	//second
	GPIO_PORTB_DATA_R = 0x30;
	en_pulse();
	us_delay(100);
	//third
	GPIO_PORTB_DATA_R = 0x30;
	en_pulse();
	ms_delay(5);
}

void lcd_write_eight_com(unsigned long com){
	GPIO_PORTB_DATA_R = (com & 0xF0);
	GPIO_PORTC_DATA_R = ((com & 0x0F)<<4);
	RS_0 = 0;
	en_pulse();
	ms_delay(5);
}

void lcd_write_com(unsigned long com){
	GPIO_PORTB_DATA_R = (com & 0xF0);
	RS_3 = 0;
	en_pulse();

	us_delay(100);

	GPIO_PORTB_DATA_R = ((com & 0x0F)<<4);
	RS_3 = 0;
	en_pulse();

	ms_delay(5);
}
void lcd_write_char(unsigned long cha){
	GPIO_PORTB_DATA_R = cha & 0xF0;
	RS_3 = 0x8;
	en_pulse();

	us_delay(100);

	GPIO_PORTB_DATA_R = ((cha & 0x0F)<<4);
	RS_3 = 0x8;
	en_pulse();

	ms_delay(5);
}
void lcd_write_eight_char(unsigned long cha){
	GPIO_PORTB_DATA_R = (cha & 0xF0);
	GPIO_PORTC_DATA_R = ((cha & 0x0F)<<4);
	RS_0 = 0x01;
	en_pulse();
	ms_delay(5);
}
