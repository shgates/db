#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

enum Result {
    SUCCESS,
    ERROR,
    ERROR_TABLE_NOT_CREATED,
    ERROR_TABLE_NOT_UPDATED,
    ERROR_PRIMARY_KEY_EXISTS,
    ERROR_PRIMARY_KEY_NOT_EXISTS,
    ERROR_TABLE_NOT_FOUND,
};

enum Type {
    UINT,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
};

// enum de opções para a função de pesquisa
enum Option {
    NUMERICAL,  // Valores numéricos (UINT, INT, FLOAT, DOUBLE)
    TEXT        // Valores de texto (CHAR, STRING)
};

/*
 * checks if user input matches with a given command
 */
bool check_command(const char input[], const char command[]);

void format_name(char* name);

enum Type string_to_type(char* type);

void type_to_string(enum Type t, char* out);

int get_num_from_user_input(char user_input[]);

bool is_number(char string_number[]);

#endif
