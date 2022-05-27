#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 1024

struct my_stack {
    int stack[STACK_SIZE];
    int idx;
};

struct my_stack *intialize_stack();
void push(struct my_stack *s, int x);
int pop(struct my_stack *s);
bool is_empty(struct my_stack *s);
int peek(struct my_stack *s);
void my_stack_free(struct my_stack *s);

#endif
