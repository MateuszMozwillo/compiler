#include "tokenizer.h"

int main() {

    char* to_tokenize = "var i = 10; function asd(v1, v2) {return v1 + v2; };";
    TokenVec tokenized = tokenize(to_tokenize, strlen(to_tokenize));

    for (size_t i = 0; i < tokenized.len; i++) {
        printf("%s ", tokenized.ptr[i].content);
    }
    printf("\n");
    
    // gives error with free
    // for (size_t i = 0; i < tokenized.len; i++) {
    //     free(tokenized.ptr[i].content);
    // }
    free(tokenized.ptr);

    return 0;
}
