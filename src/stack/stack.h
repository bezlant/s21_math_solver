/**
 * @file stack.h
 *
 * Custom stack imlementation using an array
 *
 */
#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include "../includes/common.h"

#define STACK_SIZE 256

struct my_stack {
    /**
     * @brief Array to be used as a stack
     */
    long double stack[STACK_SIZE];
    /**
     * @brief Current index in the stack
     */
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
void push(struct my_stack *const s, long double x);

/**
 * @brief Pop the top val of the stack
 *
 * @param s stack pointer
 * @return value from top of the stack
 */
long double pop(struct my_stack *s);

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
long double peek(struct my_stack *s);

/**
 * @brief destroyes the stack
 *
 * @param s stack pointer
 */
void my_stack_free(struct my_stack *s);

#endif  //  SRC_STACK_STACK_H_
