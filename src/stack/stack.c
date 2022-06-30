#include "stack.h"

struct my_stack *intialize_stack() {
    struct my_stack *new = malloc(sizeof(struct my_stack));
    if (new)
        new->idx = -1;
    return new;
}
void push(struct my_stack *s, int x) {
    s->stack[++s->idx] = x;
}
int pop(struct my_stack *s) {
    return s->stack[s->idx--];
}
bool is_empty(struct my_stack *s) {
    return s->idx >= 0 ? false : true;
}
int peek(struct my_stack *s) {
    return s->stack[s->idx];
}
void my_stack_free(struct my_stack *s) {
    free(s);
}
