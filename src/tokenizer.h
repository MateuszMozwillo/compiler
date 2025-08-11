#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "utils.h"
#include "types.h"

#define RK_LEN (size_t)7
#define SNO_LEN (size_t)14

#define STARTING_MAX_TOKEN_LEN 8
#define STARTING_MAX_TOKENIZED_LEN 64

String remove_white_space(const char* to_process, size_t to_process_len);

TokenVec tokenize(const char* to_tokenize, size_t to_tokenize_len);

void token_vec_cleanup(TokenVec tokenVec);
