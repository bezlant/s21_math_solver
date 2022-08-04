#include "parser.h"
#include "lexer.h"

int main(int argc, char *argv[]) {

    return 0;
}

char *convert_to_rpn(char **tokens, size_t size) {
    char *res = (char *)calloc(256, sizeof(char));
    CHECKMALLOC(res);

    size_t cursor = 0;
    struct my_stack *s = init_stack();

    for (size_t i = 0; i < size; i++) {
    }

    my_stack_free(s);
    return res;
}
