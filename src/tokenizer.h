#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STARTING_MAX_TOKEN_LEN 8
#define STARTING_MAX_TOKENIZED_LEN 64

extern const char* token_type_str[]; 

typedef enum {
    LITERAL,    // constant values
    IDENTFIER,  // variable/function names
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

String remove_white_space(const char* to_process, size_t to_process_len);

TokenVec tokenize(const char* to_tokenize, size_t to_tokenize_len);
