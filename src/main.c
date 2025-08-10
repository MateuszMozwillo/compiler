#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STARTING_MAX_TOKEN_LEN 8
#define STARTING_MAX_TOKENIZED_LEN 64

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

    bool token_start = false;

    size_t max_token_len = STARTING_MAX_TOKEN_LEN;
    size_t token_len = 0;
    char* token = malloc(sizeof(char)*max_token_len);

    for (size_t i = 0; i < processed.len; i++) {

        // checks for separators and operators
        for (size_t j = 0; j < sno_len; j++) {
            if (processed.str[i] == separators_and_ops[j].content[0]) {
                if (token_start) {
                    if (tokenized_len + 2 >= max_tokenized_len) {
                        max_tokenized_len *= 2;
                        tokenized = realloc(tokenized, max_tokenized_len);
                    }
                    tokenized[tokenized_len] = (Token){IDENTFIER, "", token_len};
                    strncpy(tokenized[tokenized_len].content, token, token_len);
                    tokenized_len++;
                }

                tokenized[tokenized_len] = separators_and_ops[j];
                tokenized_len++;

                // restarts current token
                max_token_len = STARTING_MAX_TOKEN_LEN;
                token_len = 0;
                token = malloc(sizeof(char)*max_token_len);

                token_start = false;
            }
        }

        // checks for reserved token
        bool is_rk_token = false;
        if (!token_start) {
            for (size_t j = 0; j < rk_len; j++) {
                if (strncmp(reserved_keywords[j].content, processed.str+i, reserved_keywords[j].content_len) == 0) {
                    is_rk_token = true;
                    i += reserved_keywords[j].content_len - 1;

                    if (tokenized_len + 1 >= max_tokenized_len) {
                        max_tokenized_len *= 2;
                        tokenized = realloc(tokenized, max_tokenized_len);
                    }
                    tokenized[tokenized_len] = reserved_keywords[j];
                    tokenized_len++;
                }
            }
        }

        if (!is_rk_token) {
            token_start = true;
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
    Token* tokenized = tokenize(to_tokenize, strlen(to_tokenize));

    for (size_t i = 0; i < 4; i++) {
        printf("TOKEN_CONTENT: [%s] ", tokenized[i].content);
    }
    
    return 0;
}
