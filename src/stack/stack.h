#ifndef STACK_H_
#define STACK_H_

#include "../includes/common.h"

#define STACK_SIZE 256

struct my_stack {
    float stack[STACK_SIZE];
    int idx;
};

struct my_stack *init_stack();
void push(struct my_stack *const s, float x);
float pop(struct my_stack *s);
bool is_empty(struct my_stack *s);
float peek(struct my_stack *s);
void my_stack_free(struct my_stack *s);

#endif
