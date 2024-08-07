#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

#ifndef TABLE_H
#define TABLE_H

#define MAX_COLUMNS 100
#define MAX_NAME_SIZE 100
#define MAX_COLUMN_NAME 100
#define MAX_STRING_SIZE 100

struct Column {
    char name[MAX_COLUMN_NAME];
    enum Type type;
    char type_s[20];
    bool is_empty;

    union {
        unsigned int data_uint;
        int data_int;
        float data_float;
        double data_double;
        char data_char;
        char data_string[MAX_STRING_SIZE];
    };
};

struct Table {
    char name[MAX_NAME_SIZE];
    unsigned int num_columns;
    unsigned int num_rows;
    unsigned int primary_key_index;
    struct Column columns[MAX_COLUMNS];
};

enum Result create_table(char* table_name);

void list_tables();

enum Result delete_table(char table_name[]);

int delete_table_file(char table_name[]);

int table_already_exists(char table_name[]);

enum Result add_data(char table_name[]);

enum Result delete_data(char table_name[], unsigned int pk);

#endif
