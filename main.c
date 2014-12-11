

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

;long main(void) {
	control();
	sys_init();

	pad_init();
	lcd_init();

	//lcd_write_char('a');

	val container_buffer[stack_size] = {'0'};
	struct buffer_stack con_buffer;
	struct buffer_stack * buffer;
	buffer = & con_buffer;
	init(container_buffer,buffer);
    double result;
/*    push('1',buffer);
    push('+',buffer);
    push('1',buffer);
    push('1',buffer);
    push('1',buffer);
    push('*',buffer);
    push('3',buffer);
    push('3',buffer);*/


/*	long test = 0;
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
    lcd_test_char();
    long i=0;
    long flag = 1;
    unsigned char input = 0;
    val null_space;
    while(1){
    	for(i=0; i<=15; i++){
    		if(pad_xvalue() != -1){
    			input = pad_value();
    			while(input == pad_value()){}
    		}
    		else{
    			i--;
    			continue;
    		}
    		if(input == 0){
    			i --;
    			continue;
    		}
    		else{
    		if(flag == 1){
    			lcd_write_com(0x01); //clean screen
    			lcd_write_com(0x02); //set ddram address to 0
    			i = 0;
    			flag = 0;
    			reinit(buffer);
    			continue;
    		}
    		if( input == 'd'){
    			pop(&null_space,buffer);
    			lcd_write_com(0x10);
    			i --;
    			continue;
    		}
    		if (input == '#'){
    			if(encoder(peek(buffer)) != NUM){
    				i --;
    				continue;
    			}
    			result = eval(buffer);
    			float2buf(buffer,result,4);
    			lcd_write_buf(buffer,1,0);
    			flag = 1;
    			continue;
    		}

    		{
    			if(encoder(input) != NUM && encoder(peek(buffer)) != NUM){ //Means it is operator
    				i--;
    				continue;
    			}
    			else{
    			push(input,buffer);
    			lcd_write_char(input);
    			}
    		}
    		}

    	}
    	flag = 1;

    }
/*
    result = eval(buffer);
    float2buf(buffer,result,4);
    lcd_write_buf(buffer,1,0);*/


    return 0;

}
