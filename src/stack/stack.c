#include "stack.h"

struct my_stack *init_stack() {
    struct my_stack *new_stack =
        (struct my_stack *)calloc(1, sizeof(struct my_stack));
    CHECKMALLOC(new_stack);

    new_stack->idx = -1;
    return new_stack;
}

void push(struct my_stack *const s, float x) {
    assert(s->idx < 1024 && s->idx >= -1);
    s->stack[++s->idx] = x;
}

float pop(struct my_stack *s) {
    assert(s != NULL);
    return s->stack[s->idx--];
}

bool is_empty(struct my_stack *s) {
    assert(s != NULL);
    return s->idx >= 0 ? false : true;
}

float peek(struct my_stack *s) {
    assert(s->idx != -1);
    return s->stack[s->idx];
}

void my_stack_free(struct my_stack *s) {
    if (s)
        free(s);
}
