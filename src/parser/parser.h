#ifndef PARSER_H_
#define PARSER_H_

#include "../includes/common.h"
#include <ctype.h>
#include <pcre.h>
#include <regex.h>
#include <string.h>

struct Tokens {
    char *token[256];
    size_t size;
};

struct Lexer {
    char *source;
    size_t cursor;
};

struct Tokens *tokenize(char *str);
void read_number(struct Lexer *lex, struct Tokens *tok);
void read_function(struct Lexer *lex, struct Tokens *tok);
void read_symbol(struct Lexer *lex, struct Tokens *tok);
void skip_spaces(struct Lexer *lex);
bool is_valid(char *str);

#endif  // PARSER_H_
