#include "lcd.h"
#include "timer.h"



void en_pulse(void){

	EN_3 = 0x08;
	us_delay(20);
	EN_3 = 0x00;

}


void lcd_init(void){

	int delay;

	SYSCTL_RCGC2_R |= 0x03;
	delay = 0;

	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0x3C;
	GPIO_PORTB_AMSEL_R &= ~0x3C;
	GPIO_PORTB_AFSEL_R &= ~0x3C;
	GPIO_PORTB_PCTL_R &= ~0xFFFF00;
	GPIO_PORTB_DIR_R |= 0x3C;
	GPIO_PORTB_DEN_R |= 0x3C;

	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R |= 0x0C;
	GPIO_PORTA_AMSEL_R &= ~0x0C;
	GPIO_PORTA_AFSEL_R &= ~0x0C;
	GPIO_PORTA_PCTL_R &= ~0xFF00;
	GPIO_PORTA_DIR_R |= 0x0C;
	GPIO_PORTA_DEN_R |= 0x0C;

	ms_delay(15);

	RS_2 = 0;
	EN_3 = 0;

	GPIO_PORTB_DATA_R = 0x0C;
	en_pulse();


	ms_delay(5);

	GPIO_PORTB_DATA_R =0x0C;
	en_pulse();

	us_delay(100);
//3
	GPIO_PORTB_DATA_R = 0x0C;
	en_pulse();
	ms_delay(100);

	GPIO_PORTB_DATA_R = 0x8;
	en_pulse();
	ms_delay(100);

	lcd_write_com(0x28);//Function Set
	lcd_write_com(0x0F);//Display on/off
	lcd_write_com(0x06);//Entry mode: Incremental

	lcd_write_com(0x01);
	//lcd_write_char(0x48);
	//lcd_write_char(0x48);

}

void lcd_write_com(unsigned long com){
	GPIO_PORTB_DATA_R = (com & 0xF0)>>2;
	RS_2 = 0;
	en_pulse();

	us_delay(100);

	GPIO_PORTB_DATA_R = (com & 0x0F)<<2;
	RS_2 = 0;
	en_pulse();

	ms_delay(5);
}
void lcd_write_char(unsigned long cha){
	GPIO_PORTB_DATA_R = (cha & 0xF0)>>2;
	RS_2 = 0x04;
	en_pulse();

	us_delay(100);

	GPIO_PORTB_DATA_R = (cha & 0x0F)<<2;
	RS_2 = 0x04;
	en_pulse();

	ms_delay(5);
}

void lcd_test_char(void){
	char table_year[8]={0x11,0x11,0x0A,0x1F,0x11,0x1B,0x15,0x1F};
	lcd_write_com(0x40);
	int i;
	for(i=0;i<=7;i++)
	{
	lcd_write_char(table_year[i]);
	}
	lcd_write_com(0x80);
	lcd_write_char(0);
}

