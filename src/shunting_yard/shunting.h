#ifndef SHUNTING_H_
#define SHUNTING_H_

#include "../includes/common.h"
#include "../stack/stack.h"

struct Tokens *convert_to_rpn(struct Tokens *expression);

#endif  // SHUNTING_H_
