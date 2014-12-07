#include <math.h>
#define stack_size 20

#include "lcd.h"

//Priority codes
#define NUM 1
#define LOWEST 9
#define MIDDLE 10
#define HIGHEST 11

typedef double val;


struct buffer_stack{
    val * base;
    val * head;
};


int init(val * con, struct buffer_stack * starter);

int pop (val * con, struct buffer_stack * node);

int push(val con, struct buffer_stack * node);

int head_loc(struct buffer_stack * node);

val peek(struct buffer_stack * node);

int encoder(val input);

double ten_pow(int num);

double stack2val(struct buffer_stack * node);

int contruct_buffer(struct buffer_stack * stack_temp, struct buffer_stack * input, struct buffer_stack * flo );

double two_eval(val exp1, val para, val exp2);

double eval(struct buffer_stack * buffer);

int float2buf(struct buffer_stack * buffer, double re, int precision);

void lcd_write_buf(struct buffer_stack * buffer, int row, int col);

int reinit(struct buffer_stack * buffer);

