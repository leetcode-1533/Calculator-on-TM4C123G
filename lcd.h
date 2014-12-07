/*
 * lcd.h
 *
 *  Created on: Nov 13, 2014
 *      Author: tk
 */

#ifndef LCD_H_
#define LCD_H_

#define SYSCTL_RCGC2_R      (*((volatile unsigned long *)0x400FE108))

#define GPIO_PORTA_DATA_R 	(*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R 	(*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R 	(*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R 	(*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R 	(*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R 	(*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R 	(*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_LOCK_R   (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_PCTL_R	(*((volatile unsigned long *)0x4000452C))

#define RS_2 (*((volatile unsigned long *)0x40004010)) //PIN A2
#define EN_3 (*((volatile unsigned long *)0x40004020)) //PIN A3



#define GPIO_PORTB_DATA_R 	(*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R 	(*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R 	(*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R 	(*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R 	(*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R 	(*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R 	(*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_LOCK_R   (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_PCTL_R	(*((volatile unsigned long *)0x4000552C))


#define GPIO_PORTC_DATA_R 	(*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R 	(*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_AFSEL_R 	(*((volatile unsigned long *)0x40006420))
#define GPIO_PORTC_PUR_R 	(*((volatile unsigned long *)0x40006510))
#define GPIO_PORTC_DEN_R 	(*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_CR_R 	(*((volatile unsigned long *)0x40006524))
#define GPIO_PORTC_AMSEL_R 	(*((volatile unsigned long *)0x40006528))
#define GPIO_PORTC_LOCK_R   (*((volatile unsigned long *)0x40006520))
#define GPIO_PORTC_PCTL_R	(*((volatile unsigned long *)0x4000652C))

void en_pulse(void);


void lcd_init(void);
void lcd_eight_init(void);

void lcd_write_com(unsigned long com);
void lcd_write_eight_com(unsigned long com);

void lcd_write_char(unsigned long cha);
void lcd_write_eight_char(unsigned long cha);

void lcd_test_char(void);

#endif /* LCD_H_ */
