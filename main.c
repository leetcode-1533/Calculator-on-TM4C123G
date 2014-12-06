

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
#include "debug.h"
#include "stack.h"

int main(void) {
	control();
	sys_init();
	int i;
	int j;

	pad_init();
	lcd_init();

	val container_buffer[stack_size] = {'0'};
	struct buffer_stack con_buffer;
	struct buffer_stack * buffer;
	buffer = & con_buffer;
	init(container_buffer,buffer);

    float result;
    push('1',buffer);
    push('+',buffer);
    push('1',buffer);
    push('1',buffer);
    push('1',buffer);
    push('*',buffer);
    push('3',buffer);
    push('3',buffer);


/*	int test = 0;
	unsigned char input= 0;
	while(1){
		for(test=0;test<=8;test++){
			if(pad_xvalue() != -1){
				input = pad_value();
				while(input == pad_value()){}
			}
			if(input == 0)
			{
				test--;
				continue;
			}
			lcd_write_char(input);
			input = 0;
		}
		lcd_write_com(0x01);
		lcd_write_com(0x02);
	}*/


    result = eval(buffer);
    float2buf(buffer,result,4);
    lcd_write_buf(buffer,1,0);



    while(1){

    }

    return 0;

}
