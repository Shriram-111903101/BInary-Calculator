#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include"list.h"
#define max 1000


typedef struct op_stack{
    int top;
    char op[max];
}op_stack;

typedef struct od_stack{
    int top;
    list *l[max];
}od_stack;

void op_push(op_stack *s, char num);
char op_pop(op_stack *s);
int op_empty(op_stack s);
int op_full(op_stack s);
void op_sinit(op_stack *s);
char op_peek(op_stack s);

void od_push(od_stack *s, list *l);
list *od_pop(od_stack *s);
int od_empty(od_stack s);
int od_full(od_stack s);
void od_sinit(od_stack *s);
list* od_peek(od_stack s);


#endif // STACK_H_INCLUDED
