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

Token* tokenize(char* to_tokenize, size_t to_tokenize_len) {
    Token* tokenized;

    String processed = remove_white_space(to_tokenize, to_tokenize_len);

    char* identifiers[] = {
        "var",
        "if",
        "else",
        "fn",
        "for",
        "while"
    };

    bool token_start = false;
    for (size_t i = 0; i < processed.len; i++) {
        
    }

    free(processed.str);
    return tokenized;
}

int main() {

    char* to_tokenize = "var i = 10;";


    return 0;
}
