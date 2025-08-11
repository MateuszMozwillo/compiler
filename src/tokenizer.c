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

TokenVec tokenize(const char* to_tokenize, size_t to_tokenize_len) {
    vec(Token) tokenized;
    vec_init(tokenized, STARTING_MAX_TOKENIZED_LEN);

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

    vec(char) token;
    vec_init(token, STARTING_MAX_TOKEN_LEN);

    for (size_t i = 0; i < processed.len; i++) {

        // checks for separators and operators
        for (size_t j = 0; j < SNO_LEN; j++) {
            if (processed.str[i] == separators_and_ops[j].content[0]) {
                if (token_start) {
                    
                    TokenType token_type = IDENTIFIER;
                    if (token.data[0] == '\"' || isdigit(token.data[0])) {
                        token_type = LITERAL;
                    }
                    Token token_to_append = (Token){token_type, "", token.len};
                    token_to_append.content = malloc(sizeof(char) * (token.len + 1));
                    if (token_to_append.content == NULL) {
                        fprintf(stderr, "Error: error when allocating");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(token_to_append.content, token.data, token.len);
                    
                    token_to_append.content[token.len] = '\0';
                    vec_append(tokenized, token_to_append);
                }
                vec_append(tokenized, separators_and_ops[j]);

                // restarts current token

                vec_cleanup(token);
                vec_init(token, STARTING_MAX_TOKEN_LEN);
                token_start = false;

                goto end_of_loop;
            }
        }

        // checks for reserved token
        if (!token_start) {
            for (size_t j = 0; j < RK_LEN; j++) {
                if (strncmp(reserved_keywords[j].content, processed.str+i, reserved_keywords[j].content_len) == 0) {
                    i += reserved_keywords[j].content_len - 1;
                    vec_append(tokenized, reserved_keywords[j]);

                    goto end_of_loop;
                }
            }
        }

        token_start = true;
        vec_append(token, processed.str[i]);

        end_of_loop:
    }
    vec_cleanup(token);
    free(processed.str);
    return (TokenVec){tokenized.data, tokenized.len};
}

void token_vec_cleanup(TokenVec tokenVec) {
    for (size_t i = 0; i < tokenVec.len; i++) {
        if (tokenVec.ptr[i].token_type == LITERAL || tokenVec.ptr[i].token_type == IDENTIFIER) {
            free(tokenVec.ptr[i].content);
        }
    }
    free(tokenVec.ptr);
}
