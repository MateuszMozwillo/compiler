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

//  TODO: add node types 
typedef enum {
    ASSIGN,
    WHILE,
    IF,
    COMPARE,
    FUNCTION_DECLARATION,
    BINARY_OPERATOR,

} AstNodeType;

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
    AstNodeType token_type;
    AstNode** nodes;
} AstNode;
