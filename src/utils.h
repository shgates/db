#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

enum Result {
    SUCCESS,
    ERROR,
    TABLE_NOT_CREATED,
    TABLE_NOT_UPDATED,
};

enum Type {
    UINT,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
};
/*
 * checks if user input matches with a given command
 */
bool check_command(const char input[], const char command[]);

void format_name(char* name);

enum Type string_to_type(char* type);

void type_to_string(enum Type t, char* out);

#endif
