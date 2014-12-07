#include "stack.h"

#include <stdio.h>



int init(val * con, struct buffer_stack * starter){
    starter -> base = con;
    starter -> head = starter->base;
    return 0;
}



int pop (val * con, struct buffer_stack * node){
    if(node->base == node->head){
        return -1;
    }else{
        node->head = node->head -1;
        * con = *(node->head);
        return 0;
    }
}

int push(val con, struct buffer_stack * node){
    if(node->head - node->base >= stack_size )
    {
        return -1;
    }
    else{
        *(node->head) = con;
        (node->head) ++;
        return 0;
    }
}



int head_loc(struct buffer_stack * node){
    return (node->head - node->base);
}



val peek(struct buffer_stack * node){
    return *((node->head)-1);
}

int encoder(val input){
    int output;
    int int_input = (char)input;
    switch(int_input){
        case '+' :
        case '-' : output = MIDDLE; break;
        case '@' : output = LOWEST; break;
        case '*' :
        case '/' : output = HIGHEST; break;
        default :
            output = NUM;
    }
    return output;
}


float ten_pow(int num){
	float temp = 1;
	if(num == 0){
		return 1;
	}
	if(num > 0){
		while(num--){
			temp = temp *10;
		}
		return temp;
	}
	if(num < 0){
		while(num++){
			temp = temp*0.1;
		}
		return temp;
	}
}

float stack2val(struct buffer_stack * node){
    int i = 0;
    float temp_sum = 0.0;
    val temp_elem;
    char char_temp;
    float float_temp;
    while(head_loc(node) != 0){
        pop(&temp_elem, node);
        char_temp = (char)temp_elem;
        char_temp -= '0';
        float_temp = char_temp + 0.0;
        temp_sum += float_temp*ten_pow(i++);
    }
    return temp_sum;
}



int construct_buffer(struct buffer_stack * input,struct buffer_stack * flo){

	val stack_temp_container[stack_size];
	struct buffer_stack stack_temp_con;
	struct buffer_stack * stack_temp;
	stack_temp = & stack_temp_con;
	init(stack_temp_container,stack_temp);

    val temp;

    while(head_loc(input) != 0){
        pop(&temp,input);
        if(encoder(temp) == NUM){
            push(temp,stack_temp);
        }
        else{
            push(stack2val(stack_temp),flo);
            push(temp,flo);
        }
        }
        push(stack2val(stack_temp),flo);
    return 0;
}

float two_eval(val exp1, val para, val exp2){

    char code = (char) para;
    switch(code){
        case '+' : return (exp1 + exp2); break;
        case '-' : return (exp1 - exp2); break;
        case '*' : return (exp1 * exp2); break;
        case '/' : return (exp1 / exp2); break;
        default :
            return -1;
    }
}

float eval(struct buffer_stack * buffer){

    val flo_container[stack_size] = {0};
    struct buffer_stack  flo_con;
    struct buffer_stack * flo;
    flo = & flo_con;
    init(flo_container,flo);

    val container_oper[stack_size] = {0};
    val container_numb[stack_size] = {0} ;
    struct buffer_stack con_oper;
    struct buffer_stack con_numb;

    struct buffer_stack * oper;
    struct buffer_stack * numb;

    oper = & con_oper;
    numb = & con_numb;

    init(container_oper,oper);
    init(container_numb,numb);

    push('@',oper);
    construct_buffer(buffer,flo);

    val inspector;
    int code;
    val exp1;
    val para;
    val exp2;

    float temp_result;

    do{
      //temp_debug(buffer);

      //stage 1
      if(head_loc(flo) != 0){
        pop(&inspector,flo);
        code = encoder(inspector);
        if(code == NUM)
        {
            push(inspector,numb);
        }
        else if( code > encoder(peek(oper)) )
        {
            push(inspector,oper);
        }
        else if( code <= encoder(peek(oper)) ){ //exp1 para exp2
            pop(&exp2,numb);
            pop(&para,oper);
            pop(&exp1,numb);
            temp_result = two_eval(exp1,para,exp2);
            push(temp_result,numb);
            push(inspector,flo);
        }
      }
      //stag two
      else if(peek(oper) != '@'){
            pop(&exp2,numb);
            pop(&para,oper);
            pop(&exp1,numb);
            temp_result = two_eval(exp1,para,exp2);
            push(temp_result,numb);
      }
      }while( peek(oper) != '@' || head_loc(flo) != 0 );

    pop(&temp_result,numb);
    return temp_result;
}

int float2buf(struct buffer_stack * buffer, float re,int precision){
	int minus_flag = 0;
	int dec_flag = 0;

	if(re < 0){
		minus_flag = 1;
		re = -re;
	}
	int decval; // decimal value;
	int intval; //integer value;
	re = re + 5 * ten_pow(- precision - 1);
	decval = (int)(re *(int)ten_pow(precision))%((int)ten_pow(precision));
	if(decval != 0){
		dec_flag = 1;
	}
	while(decval > 0){
		push((decval % 10+ '0') , buffer);
		decval = decval / 10;
	}
	if(dec_flag == 1){
		push('.',buffer);
	}

	intval = (int)re;
	while(intval>0){
		push((intval % 10 + '0') , buffer );
		intval = intval / 10;
	}
	if(minus_flag == 1){
		push('-',buffer);
	}
	return 0;
}

void lcd_write_buf(struct buffer_stack * buffer, int row, int col){
	int com_address = 0;
	char temp_char;
	val val_temp;
	switch(row){
		case 0: com_address = 0x80 + col; break;
		case 1: com_address = 0xC0 + col; break;
	}
	lcd_write_com(com_address);
	while(head_loc(buffer) != 0){
		pop(&val_temp,buffer);
		temp_char = (char)val_temp;
		lcd_write_char(temp_char);
	}
}

int reinit(struct buffer_stack * buffer){
	buffer->head = buffer->base;
	return 0;
}




