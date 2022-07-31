#ifndef STACK_H_
#define STACK_H_

#include "../includes/common.h"

#define STACK_SIZE 1024

struct my_stack {
    long double stack[STACK_SIZE];
    int idx;
};

struct my_stack *init_stack();
void push(struct my_stack *const s, long double x);
long double pop(struct my_stack *s);
bool is_empty(struct my_stack *s);
long double peek(struct my_stack *s);
void my_stack_free(struct my_stack *s);

#endif
