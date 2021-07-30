#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "list.h"

void op_sinit(op_stack *s){
    s -> top = -1;
}

int op_empty(op_stack s){
    if(s.top == -1)
        return 1;
    else
        return 0;
}

int op_full(op_stack s){
    if(s.top == max - 1)
        return 1;
    else
        return 0;
}

void op_push(op_stack *s, char ch){
    if(op_full(*s))
        return;
    else{
        (s -> top)++;
        s -> op[s -> top] = ch;
        return;
    }
}

char op_pop(op_stack *s){
    if(op_empty(*s))
        return 0;
    else{
        char ch = s -> op[s -> top];
        (s -> top)--;
        return ch;
    }
}

char op_peek(op_stack s){
    if(op_empty(s))
        return '#';
    else
        return s.op[s.top];
}

void od_sinit(od_stack *s){
    s -> top = -1;
}

int od_empty(od_stack s){
    if(s.top == -1){
        return 1;
    }
    else
        return 0;
}

int od_full(od_stack s){
    if(s.top == max - 1)
        return 1;
    else
        return 0;
}

void od_push(od_stack *s, list *l){
    if(od_full(*s))
        return;
    else{
        (s -> top)++;
        s -> l[s -> top] = l;
        return;
    }
}

list* od_pop(od_stack *s){
    list *p = (list*)malloc(sizeof(list));
    if(od_empty(*s))
        return 0;
    else{
        p = s -> l[s -> top];
        (s->top)--;
        return p;
    }
}

list* od_peek(od_stack s){
    if(od_empty(s))
        return 0;
    else
        return s.l[s.top];
}


