#include "tokenizer.h"

int main() {

    char* to_tokenize = "var i = 10; function asd(v1, v2) {return v1 + v2; };";
    TokenVec tokenized = tokenize(to_tokenize, strlen(to_tokenize));

    printf("\n");
    for (size_t j = 0; j < 100000000; j++) {
        TokenVec tokenized = tokenize(to_tokenize, strlen(to_tokenize));
        token_vec_cleanup(tokenized);
        if (j % 10000 == 0) {
            printf("%lld\n", j);
        }
        
    }

    // for (size_t i = 0; i < tokenized.len; i++) {
    //     printf(" %s" , tokenized.ptr[i].content);
    // }
    

    token_vec_cleanup(tokenized);

    return 0;
}
