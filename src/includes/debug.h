#include <stdbool.h>

#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef NDEBUG
#define TRACE_ON 0
#else
#define TRACE_ON 1
#endif

#define STRINGIFY(X) #X
#define STRGY(X) STRINGIFY(X)

#define TRACE_PRINT(F, X)                                                      \
    do {                                                                       \
        if (TRACE_ON)                                                          \
            fprintf(stderr, "%s:" STRGY(__LINE__) ":(" #X "): " F "\n",        \
                    __func__, X);                                              \
    } while (false)

#define TRACE_VALUE(TEXT, X) TRACE_PRINT(TEXT " %Lg", (X) + 0.0L)
#define TRACE_PTR(TEXT, X) TRACE_PRINT(TEXT " %p", ((void *){0} = (X)))

#endif  // DEBUG_H_
