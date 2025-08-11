#pragma once

#include <stdlib.h>

#define MEM_ALLOCATION_ERROR_MSG "Error: allocating memory failed"

#define vec(type) struct { \
    type *data; \
    size_t len; \
    size_t capacity; \
}

#define vec_init(vec, starting_capacity) do { \
    (vec).data = malloc(sizeof(*(vec).data) * (starting_capacity)); \
    if ((vec).data == NULL) { \
        fprintf(stderr, MEM_ALLOCATION_ERROR_MSG); \
        exit(EXIT_FAILURE); \
    } \
    (vec).len = 0; \
    (vec).capacity = (starting_capacity); \
} while (0)

#define vec_append(vec, to_append) do { \
    if ((vec).len + 1 >= (vec).capacity) { \
        (vec).capacity *= 2; \
        (vec).data = realloc((vec).data, sizeof(*(vec).data) * (vec).capacity); \
        if ((vec).data == NULL) { \
            fprintf(stderr, MEM_ALLOCATION_ERROR_MSG); \
            exit(EXIT_FAILURE); \
        } \
    } \
    (vec).data[(vec).len] = (to_append); \
    (vec).len++; \
} while(0)

#define vec_cleanup(vec) do { \
    free((vec).data); \
} while(0)
