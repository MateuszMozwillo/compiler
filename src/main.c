#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#include <time.h>
#include <windows.h>

typedef enum {
    LITERAL,    // constant values
    IDENTFIER,  // if else ...
    KEYWORD,    // variable/function names 
    OPERATOR,   // + - ...
    SEPARATOR,  // { ; ...
} TokenType;

typedef struct {
    TokenType tokenType;
    char* content;
} Token;

char* RemoveWhiteSpace(const char* toProcess, size_t toProcessLen) {
    size_t finalLen = 0;
    for (size_t i = 0; i < toProcessLen; i++) {
        if (!isspace(toProcess[i])) {
            finalLen++;
        } 
    }

    size_t j = 0;
    char* processed = malloc(sizeof(char)*(finalLen+1));

    for (size_t i = 0; i < toProcessLen; i++) {
        if (!isspace(toProcess[i])) {
            processed[j] = toProcess[i];
            j++;
        }
    }
    processed[finalLen] = '\0';

    return processed;
}

Token* Tokenize(char* toTokenize, size_t toTokenizeLen) {
    Token* tokenized;

    char* processed = RemoveWhiteSpace(toTokenize, toTokenizeLen);
    printf("%s\n", processed);

    free(processed);
    return tokenized;
}

int main() {

    char* to_tokenize = "int i = 10;";


    return 0;
}
