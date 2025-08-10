#include "tokenizer.h"

String remove_white_space(const char* to_process, size_t to_process_len) {
    size_t final_len = 0;
    for (size_t i = 0; i < to_process_len; i++) {
        if (!isspace(to_process[i])) {
            final_len++;
        } 
    }

    size_t j = 0;
    char* processed = malloc(sizeof(char)*(final_len+1));
    if (processed == NULL) {
        fprintf(stderr, "Error: error when allocating");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < to_process_len; i++) {
        if (!isspace(to_process[i])) {
            processed[j] = to_process[i];
            j++;
        }
    }
    processed[final_len] = '\0';

    return (String){processed, final_len};
}

// TODO: wrap mallocs and reallocs into vector structs

TokenVec tokenize(const char* to_tokenize, size_t to_tokenize_len) {
    size_t tokenized_len = 0;
    size_t max_tokenized_len = STARTING_MAX_TOKENIZED_LEN;
    Token* tokenized = malloc(sizeof(Token)*max_tokenized_len);
    if (tokenized == NULL) {
        fprintf(stderr, "Error: error when allocating");
        exit(EXIT_FAILURE);
    }

    String processed = remove_white_space(to_tokenize, to_tokenize_len);

    const Token reserved_keywords[RK_LEN] = {
        (Token){KEYWORD, "var", 3},
        (Token){KEYWORD, "if", 2},
        (Token){KEYWORD, "else", 4},
        (Token){KEYWORD, "function", 8},
        (Token){KEYWORD, "for", 3},
        (Token){KEYWORD, "while", 5},
        (Token){KEYWORD, "return", 6},
    };

    const Token separators_and_ops[SNO_LEN] = {
        (Token){SEPARATOR, ";", 1},
        (Token){SEPARATOR, "(", 1},
        (Token){SEPARATOR, ")", 1},
        (Token){SEPARATOR, "{", 1},
        (Token){SEPARATOR, "}", 1},
        (Token){SEPARATOR, ",", 1},
        (Token){SEPARATOR, "\"", 1},

        (Token){OPERATOR, "-", 1},
        (Token){OPERATOR, "+", 1},
        (Token){OPERATOR, "/", 1},
        (Token){OPERATOR, "*", 1},
        (Token){OPERATOR, "%", 1},
        (Token){OPERATOR, "!", 1},
        (Token){OPERATOR, "=", 1},
    };

    bool token_start = false;

    size_t max_token_len = STARTING_MAX_TOKEN_LEN;
    size_t token_len = 0;
    char* token = malloc(sizeof(char)*max_token_len);
    if (token == NULL) {
        fprintf(stderr, "Error: error when allocating");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < processed.len; i++) {

        // checks for separators and operators
        for (size_t j = 0; j < SNO_LEN; j++) {
            if (processed.str[i] == separators_and_ops[j].content[0]) {
                if (token_start) {
                    if (tokenized_len + 2 >= max_tokenized_len) {
                        max_tokenized_len *= 2;
                        tokenized = realloc(tokenized, sizeof(Token)*max_tokenized_len);
                        if (tokenized == NULL) {
                            fprintf(stderr, "Error: error when allocating");
                            exit(EXIT_FAILURE);
                        }
                    }
                    TokenType token_type = IDENTIFIER;
                    if (token[0] == '\"' || isdigit(token[0])) {
                        token_type = LITERAL;
                    }
                    tokenized[tokenized_len] = (Token){token_type, "", token_len};
                    tokenized[tokenized_len].content = malloc(sizeof(char) * (token_len + 1));
                    if (tokenized[tokenized_len].content == NULL) {
                        fprintf(stderr, "Error: error when allocating");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(tokenized[tokenized_len].content, token, token_len);
                    tokenized[tokenized_len].content[token_len] = '\0';
                    tokenized_len++;
                }

                tokenized[tokenized_len] = separators_and_ops[j];
                tokenized_len++;

                // restarts current token
                max_token_len = STARTING_MAX_TOKEN_LEN;
                token_len = 0;
                free(token);
                token = malloc(sizeof(char)*max_token_len);
                if (token == NULL) {
                    fprintf(stderr, "Error: error when allocating");
                    exit(EXIT_FAILURE);
                }
                token_start = false;

                goto end_of_loop;
            }
        }

        // checks for reserved token
        if (!token_start) {
            for (size_t j = 0; j < RK_LEN; j++) {
                if (strncmp(reserved_keywords[j].content, processed.str+i, reserved_keywords[j].content_len) == 0) {
                    i += reserved_keywords[j].content_len - 1;

                    if (tokenized_len + 1 >= max_tokenized_len) {
                        max_tokenized_len *= 2;
                        tokenized = realloc(tokenized, sizeof(Token)*max_tokenized_len);
                        if (tokenized == NULL) {
                            fprintf(stderr, "Error: error when allocating");
                            exit(EXIT_FAILURE);
                        }
                    }
                    tokenized[tokenized_len] = reserved_keywords[j];
                    tokenized_len++;

                    goto end_of_loop;
                }
            }
        }

        token_start = true;
        if (token_len + 2 >= max_token_len) {
            max_token_len *= 2;
            token = realloc(token, max_token_len);
            if (token == NULL) {
                fprintf(stderr, "Error: error when allocating");
                exit(EXIT_FAILURE);
            }
        }
        token[token_len] = processed.str[i];
        token_len += 1;
        end_of_loop:
    }
    free(token);
    free(processed.str);
    return (TokenVec){tokenized, tokenized_len};
}

void token_vec_cleanup(TokenVec tokenVec) {
    for (size_t i = 0; i < tokenVec.len; i++) {
        if (tokenVec.ptr[i].token_type == LITERAL || tokenVec.ptr[i].token_type == IDENTIFIER) {
            free(tokenVec.ptr[i].content);
        }
    }
    free(tokenVec.ptr);
}
