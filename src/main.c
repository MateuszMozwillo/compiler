#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {
    LITERAL,    // constant values
    IDENTFIER,  // if else ...
    KEYWORD,    // variable/function names 
    OPERATOR,   // + - ...
    SEPARATOR,  // { ; ...
} TokenType;

typedef struct {
    TokenType token_type;
    char* content;
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

/* 
    will break if to_check_offset >= strlen(to_check)
    returns token length else -1
*/
int _check_for_token_type(const char* to_check, size_t to_check_offset) {
    
    const size_t rt_count = 17;
    const char* reserved_tokens[17] = {
        "var",
        "if",
        "else",
        "fn",
        "for",
        "while",

        ";",
        "(",
        ")",
        "{",
        "}",

        "-",
        "+",
        "/",
        "*",
        "%",
        "!",
    };
    const size_t rt_lengths[17] = {3, 2, 4, 2, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    for (size_t i = 0; i < rt_count; i++) {
        if (strncmp(reserved_tokens[i], to_check+to_check_offset, rt_lengths[i]) == 0) {
            return rt_lengths[i];
        };
    }
    return -1;
}

Token* tokenize(const char* to_tokenize, size_t to_tokenize_len) {
    Token* tokenized;

    String processed = remove_white_space(to_tokenize, to_tokenize_len);

    bool token_start = false;

    size_t current_possible_token_len = 8;
    size_t current_token_len = 0;
    char* possible_token = malloc(sizeof(char)*current_possible_token_len);
    
    for (size_t i = 0; i < processed.len; i++) {

    }

    free(processed.str);
    return tokenized;
}

int main() {
    
    char* to_tokenize = "var i = 10;";


    return 0;
}
