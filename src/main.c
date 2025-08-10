#include "tokenizer.h"

int main() {

    char* to_tokenize = "var i = 10; function asd(v1, v2) {return v1 + v2; };";
    TokenVec tokenized = tokenize(to_tokenize, strlen(to_tokenize));

    for (size_t i = 0; i < tokenized.len; i++) {
        printf("%s ", tokenized.ptr[i].content);
    }
    printf("\n");

    token_vec_cleanup(tokenized);

    return 0;
}
