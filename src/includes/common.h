#ifndef COMMON_H_
#define COMMON_H_

#include "debug.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECKMALLOC(var)                                                       \
    if ((var) == NULL) {                                                       \
        fprintf(stderr, "ERROR: Memory allocation failed\n");                  \
        abort();                                                               \
    }

#endif  // COMMON_H_
