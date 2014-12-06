#define stack_size 20

//Priority codes
#define NUM 1
#define LOWEST 9
#define MIDDLE 10
#define HIGHEST 11

typedef float val;


struct buffer_stack{
    val * base;
    val * head;
    int current_size;
};



int init(val * con, struct buffer_stack * starter);

int pop (val * con, struct buffer_stack * node);

int push(val con, struct buffer_stack * node);

int head_loc(struct buffer_stack * node);

val peek(struct buffer_stack * node);

float eval(struct buffer_stack * buffer);

float two_eval(val exp1, val para, val exp2);

int encoder(val input);

int stack2str(char * str, struct buffer_stack * node);

int single_reverse(struct buffer_stack * input, struct buffer_stack * target);

int buffer_reverse(struct buffer_stack * head);

int contruct_buffer(struct buffer_stack * input, struct buffer_stack * flo );
