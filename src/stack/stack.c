#include "stack.h"

/**
 * @brief Creates a new instance of an array based stack
 * struct my_stack {
 *  int stack[STACK_SIZE];
 *  int idx;
 *  };
 */
struct my_stack *init_stack() {
    struct my_stack *new_stack =
        (struct my_stack *)calloc(1, sizeof(struct my_stack));

    assert(new_stack != NULL);

    new_stack->idx = -1;
    return new_stack;
}

/**
 * @brief Push on top of the stack
 *
 * @param s stack pointer
 * @param x value to add to the stack
 */
void push(struct my_stack *const s, long double x) {
    assert(s->idx < 1024 && s->idx >= -1);
    s->stack[++s->idx] = x;
}

/**
 * @brief Pop the top val of the stack
 *
 * @param s stack pointer
 * @return value from top of the stack
 */
long double pop(struct my_stack *s) {
    assert(s != NULL);
    return s->stack[s->idx--];
}
/**
 * @brief Check if stack is empty
 *
 * @param s stack pointer
 * @return true if empty otherwise false
 */
bool is_empty(struct my_stack *s) {
    assert(s != NULL);
    return s->idx >= 0 ? false : true;
}

/**
 * @brief peeks at the top value of the stack
 *
 * @param s stack pointer
 * @return the top value
 */
long double peek(struct my_stack *s) {
    assert(s->idx != -1);
    return s->stack[s->idx];
}

/**
 * @brief destroyes the stack
 *
 * @param s stack pointer
 */
void my_stack_free(struct my_stack *s) {
    if (s)
        free(s);
}
