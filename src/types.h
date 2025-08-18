#pragma once

#include <stdlib.h>

extern const char* token_type_str[]; 

typedef enum {
    LITERAL,    // constant values
    IDENTIFIER,  // variable/function names
    KEYWORD,    // if var...
    OPERATOR,   // + -...
    SEPARATOR,  // { ;...
} TokenType;

typedef struct {
    TokenType token_type;
    char* content;
    size_t content_len;
} Token;

typedef struct {
    char* str;
    size_t len;
} String;

typedef struct {
    Token* ptr;
    size_t len;
} TokenVec;

typedef struct {
    LstToken** nodes;
    
} LstToken;
