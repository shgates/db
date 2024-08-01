#include <stdio.h>

#include "utils.h"

enum Errors create_table(char* input, size_t input_len) {
    printf("Input:");
    for (size_t i = 0; i < input_len; i++) {
        printf("%c", input[i]);
    }
    printf("\n");
    return TABLE_NOT_CREATED;
}

void list_tables() { puts("Tables here"); }
