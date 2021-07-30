#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct node{
    int dig;
    struct node* next;
}node;

typedef struct list{
    node* head;
    int sign;
    int dec;
}list;

void linit(list* l);
int length(list l);
void insert(list* l, int pos, int d);
void append(list *l, int num);
int display(list l, int pos);
void traverse(list l);
list* add(list *l1, list *l2);
list* sub(list *l1, list *l2);
list* mul(list *l1, list *l2);
list* division(list *l1, list *l2);
void remove_zero(list *l);
int compare(list *l1, list *l2);

#endif // LIST_H_INCLUDED
