#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool check_command(const char input[], const char command[]) {
    if (strncmp(input, command, strlen(command)) == 0) {
        return true;
    }
    return false;
}

void format_name(char* name) {
    for (size_t i = 0; i < strlen(name); i++) {
        if (name[i] == ' ') name[i] = '_';
    }
}

enum Type string_to_type(char* type) {
    for (size_t i = 0; i < strlen(type); i++) {
        type[i] = tolower(type[i]);
    }
    if (strcmp(type, "uint") == 0)
        return UINT;
    else if (strcmp(type, "int") == 0)
        return INT;
    else if (strcmp(type, "float") == 0)
        return FLOAT;
    else if (strcmp(type, "double") == 0)
        return DOUBLE;
    else if (strcmp(type, "char") == 0)
        return CHAR;
    else if (strcmp(type, "string") == 0)
        return STRING;
    else
        return -1;
}
void type_to_string(enum Type t, char* out) {
    switch (t - 1) {
        case UINT:
            strcpy(out, "uint");
            break;
        case INT:
            strcpy(out, "int");
            break;
        case FLOAT:
            strcpy(out, "float");
            break;
        case DOUBLE:
            strcpy(out, "double");
            break;
        case CHAR:
            strcpy(out, "char");
            break;
        case STRING:
            strcpy(out, "string");
            break;
        default:
            strcpy(out, "unknown");
            break;
    }
}

int get_num_from_user_input(char user_input[]) {
    size_t size = strlen(user_input);
    char copy[size];
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (isdigit(user_input[i])) {
            copy[count] = user_input[i];
            count++;
        }
        else {
            break;
        }
    }
    return atoi(copy);
}

bool is_number(char string_number[]) {
    size_t size = strlen(string_number);
    for (size_t i = 0; i < size; i++) {
        if (string_number[i] == '.' || string_number[i] == ',') {
            continue;
        }
        if (!isdigit(string_number[i])) {
            return false;
        }
    }
    return true;
}
