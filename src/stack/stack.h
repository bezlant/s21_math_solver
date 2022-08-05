#ifndef STACK_H_
#define STACK_H_

#include "../includes/common.h"

#define STACK_SIZE 256

struct my_stack {
    float stack[STACK_SIZE];
    int idx;
};

/**
 * @brief Creates a new instance of an array based stack
 * struct my_stack {
 *  int stack[STACK_SIZE];
 *  int idx;
 *  };
 */
struct my_stack *init_stack();

/**
 * @brief Push on top of the stack
 *
 * @param s stack pointer
 * @param x value to add to the stack
 */
void push(struct my_stack *const s, float x);

/**
 * @brief Pop the top val of the stack
 *
 * @param s stack pointer
 * @return value from top of the stack
 */
float pop(struct my_stack *s);

/**
 * @brief Check if stack is empty
 *
 * @param s stack pointer
 * @return true if empty otherwise false
 */
bool is_empty(struct my_stack *s);

/**
 * @brief peeks at the top value of the stack
 *
 * @param s stack pointer
 * @return the top value
 */
float peek(struct my_stack *s);

/**
 * @brief destroyes the stack
 *
 * @param s stack pointer
 */
void my_stack_free(struct my_stack *s);

#endif
