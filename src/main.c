#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STARTING_POSSIBLE_TOKEN_LEN 8
#define STARTING_TOKEN_CONTENT_LEN 8
#define STARTING_TOKEN_LIST_SIZE 64

typedef enum {
    LITERAL,    // constant values
    IDENTFIER,  // variable/function names
    KEYWORD,    // if else ...
    OPERATOR,   // + - ...
    SEPARATOR,  // { ; ...
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

String remove_white_space(const char* to_process, size_t to_process_len) {
    size_t final_len = 0;
    for (size_t i = 0; i < to_process_len; i++) {
        if (!isspace(to_process[i])) {
            final_len++;
        } 
    }

    size_t j = 0;
    char* processed = malloc(sizeof(char)*(final_len+1));

    for (size_t i = 0; i < to_process_len; i++) {
        if (!isspace(to_process[i])) {
            processed[j] = to_process[i];
            j++;
        }
    }
    processed[final_len] = '\0';

    return (String){processed, final_len};
}

Token* tokenize(const char* to_tokenize, size_t to_tokenize_len) {
    Token* tokenized;

    String processed = remove_white_space(to_tokenize, to_tokenize_len);
    
    const size_t rt_len = 17;
    const Token reserved_tokens[17] = {
        (Token){KEYWORD, "var", 3},
        (Token){KEYWORD, "if", 2},
        (Token){KEYWORD, "else", 4},
        (Token){KEYWORD, "fn", 2},
        (Token){KEYWORD, "for", 3},
        (Token){KEYWORD, "while", 5},
        (Token){SEPARATOR, ";", 1},
        (Token){SEPARATOR, "(", 1},
        (Token){SEPARATOR, ")", 1},
        (Token){SEPARATOR, "{", 1},
        (Token){SEPARATOR, "}", 1},
        (Token){OPERATOR, "-", 1},
        (Token){OPERATOR, "+", 1},
        (Token){OPERATOR, "/", 1},
        (Token){OPERATOR, "*", 1},
        (Token){OPERATOR, "%", 1},
        (Token){OPERATOR, "!", 1},
    };

    bool token_start = false;

    size_t current_possible_token_len = STARTING_POSSIBLE_TOKEN_LEN;
    size_t current_token_len = 0;
    char* possible_token = malloc(sizeof(char)*current_possible_token_len);

    for (size_t i = 0; i < processed.len; i++) {

        for (size_t j = 0; j < rt_len; j++) {
            if (strncmp(reserved_tokens[j].content, processed.str+i, reserved_tokens[j].content_len) == 0) {
                
            };
        }
    }
    
    free(processed.str);
    return tokenized;
}

int main() {
    
    char* to_tokenize = "var i = 10;";


    return 0;
}
