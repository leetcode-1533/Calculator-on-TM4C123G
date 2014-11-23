#include "lcd.h"
#include "timer.h"

void en_pulse(void){
	EN_2 = 0x04;
	us_delay(20);
	EN_2 = 0;
}

void lcd_init(void){

	int delay;

	SYSCTL_RCGC2_R |= 0x03;
	delay = 0;

	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R |= 0x0C;
	GPIO_PORTA_AMSEL_R &= ~0x0C;
	GPIO_PORTA_AFSEL_R &= ~0x0C;
	GPIO_PORTA_PCTL_R &= ~0x0C;
	GPIO_PORTA_DIR_R |= 0x0C;
	GPIO_PORTA_DEN_R |= 0x0C;

	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xF0;
	GPIO_PORTB_AMSEL_R &= ~0xF0;
	GPIO_PORTB_AFSEL_R &= ~0xF0;
	GPIO_PORTB_PCTL_R &= ~0xF0;
	GPIO_PORTB_DIR_R |= 0xF0;
	GPIO_PORTB_DEN_R |= 0xF0;

	ms_delay(15);

	RS_3 = 0;
	EN_2 = 0;

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

	lcd_write_com(0x1C);
	lcd_write_com(0x08);
	lcd_write_com(0x01);
	lcd_write_com(0x07);


}

void lcd_8_init(void){

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
