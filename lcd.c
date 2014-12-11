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
	char table_year[8][8]=
	{{0x00,0x00,0x00,0x03,0x06,0x04,0x04,0x00},
			{0x00,0x00,0x00,0x10,0x0C,0x02,0x01,0x01},
			{0x00,0x00,0x06,0x06,0x05,0x09,0x11,0x10},
			{0x01,0x01,0x02,0x0C,0x19,0x1D,0x06,0x00},
			{0x18,0x08,0x08,0x18,0x1F,0x08,0x0B,0x06},
			{0x00,0x00,0x00,0x01,0x1F,0x04,0x1C,0x00},
			{0x00,0x0F,0x08,0x1F,0x18,0x00,0x00,0x00},
			{0x00,0x00,0x1C,0x1E,0x00,0x00,0x00,0x00}};
	lcd_write_com(0x40);
	char address_table[8] = {0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78};
	int i;
	int j;
	for (j = 0; j <= 7; j++){
		lcd_write_com(address_table[j]);
		for(i=0;i<=7;i++)
		{
			lcd_write_char(table_year[j][i]);
		}
	}
	lcd_write_com(0x80);
	for ( j = 0; j <=7 ; j++){
	lcd_write_char(j);
	}
}

