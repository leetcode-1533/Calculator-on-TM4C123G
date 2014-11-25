

#define PF2                     (*((volatile unsigned long *)0x40025010))

#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002553C))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))



#define SYSCTL_RCGC2_R			(*((volatile unsigned long *)0x400FE108))

#include "timer.h"
#include "pad.h"
//#include "debug.h"
#include "lcd.h"


int main(void) {
	control();
	sys_init();

	//ConfigureUART();
	pad_init();
	lcd_init();

	lcd_write_com(0x20);
	lcd_write_com(0x0E);
	lcd_write_com(0x06);

	lcd_write_com(0x01);
	lcd_write_char(0x48);
	lcd_write_char(0x48);

	int test = 0;
	unsigned char input;
	while(1){
		for(test=0;test<=8;test++){
			input = pad_value();
			if(input == 0){
				test --;
				continue;
			}
			lcd_write_char(input);
		}
		lcd_write_com(0x01);
		lcd_write_com(0x02);
	}
}
