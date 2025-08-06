#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STARTING_MAX_TOKEN_LEN 8
#define STARTING_MAX_TOKENIZED_LEN 64

typedef enum {
    NOT_DETERMINED,
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

void _tokenized_append(Token* tokenized, size_t* current_t_len, size_t* max_t_len, Token token_to_append) {
    if (*current_t_len >= max_t_len - 1) {
        *max_t_len *= 2;
        tokenized = realloc(tokenized, sizeof(Token)**max_t_len);
    }
    tokenized[*current_t_len] = token_to_append;
    *current_t_len++; 
}

Token* tokenize(const char* to_tokenize, size_t to_tokenize_len) {
    size_t tokenized_len = 0;
    size_t max_tokenized_len = STARTING_MAX_TOKENIZED_LEN;
    Token* tokenized = malloc(sizeof(Token)*max_tokenized_len);

    String processed = remove_white_space(to_tokenize, to_tokenize_len);

    const size_t rk_len = 6;
    const Token reserved_keywords[6] = {
        (Token){KEYWORD, "var", 3},
        (Token){KEYWORD, "if", 2},
        (Token){KEYWORD, "else", 4},
        (Token){KEYWORD, "function", 2},
        (Token){KEYWORD, "for", 3},
        (Token){KEYWORD, "while", 5},
    };

    const size_t sno_len = 12;
    const Token separators_and_ops[12] = {
        (Token){SEPARATOR, ";", 1},
        (Token){SEPARATOR, "(", 1},
        (Token){SEPARATOR, ")", 1},
        (Token){SEPARATOR, "{", 1},
        (Token){SEPARATOR, "}", 1},
        (Token){SEPARATOR, "\"", 1},

        (Token){OPERATOR, "-", 1},
        (Token){OPERATOR, "+", 1},
        (Token){OPERATOR, "/", 1},
        (Token){OPERATOR, "*", 1},
        (Token){OPERATOR, "%", 1},
        (Token){OPERATOR, "!", 1},
    };

    bool token_start = true;

    size_t max_token_len = STARTING_MAX_TOKEN_LEN;
    size_t token_len = 0;
    char* token = malloc(sizeof(char)*max_token_len);

    for (size_t i = 0; i < processed.len; i++) {

        for (size_t j = 0; j < sno_len; j++) {
            if (processed.str[i] == separators_and_ops[j].content[0]) {
                if (token_start) {
                    if (tokenized_len + 1 >= max_tokenized_len) {
                        max_tokenized_len *= 2;
                        tokenized = realloc(tokenized, max_tokenized_len);
                    }
                    // TODO: fix  this
                    tokenized[tokenized_len] = (Token){NOT_DETERMINED, "", token_len};
                    strncpy(tokenized[tokenized_len].content, token, token_len);
                    tokenized_len += 1;

                    tokenized[tokenized_len];
                }
                token_start = false;
            }
        }

        bool is_rk_token = false;
        if (token_start) {
            for (size_t j = 0; j < rk_len; j++) {
                if (strncmp(reserved_keywords[j].content, processed.str+i, reserved_keywords[j].content_len) == 0) {
                    is_rk_token = true;
                }
            }
        }

        if (!is_rk_token) {
            token_start = false;
            if (token_len + 1 >= max_token_len) {
                max_token_len *= 2;
                token = realloc(token, max_token_len);
            }
            token[token_len] = processed.str[i];
            token_len += 1;
        } 
    }

    free(processed.str);
    return tokenized;
}

int main() {

    char* to_tokenize = "var i = 10;";

    return 0;
}
