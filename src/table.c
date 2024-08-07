
#include "table.h"

#include <stdio.h>
#include <string.h>

#include "messages.h"
#include "utils.h"

#define MAX_PATH_SIZE 1000
#define MAX_TABLE_QUANTITY 100
#define MAX_TABLE_NAME_SIZE 100

const char* TABLE_LIST_FORMAT_IN = "%s %u %u\n";
const char* TABLE_LIST_FORMAT_OUT = "%s %u %u\n";
const char* TABLE_COLUMN_FORMAT = "%s %s |";

const char* TABLE_ROW_FORMAT = "%s";

static char FILE_PATH[MAX_PATH_SIZE];

static char MAIN_FILE_PATH[] = "./db/listoftables.txt";

// static struct Table tables[MAX_TABLE_QUANTITY];

enum Result persist_table(struct Table* t) {
    char path[MAX_PATH_SIZE];
    sprintf(path, "./db/%s.txt", t->name);
    FILE* f = fopen(path, "w");
    if (f == NULL) {
        printf("An error occured when trying to persist %s table", t->name);
        return ERROR;
    }
    fprintf(f, TABLE_COLUMN_FORMAT, "uint", t->columns[0].name);

    for (size_t i = 1; i < t->num_columns; i++) {
        fprintf(f, " ");
        fprintf(
            f, TABLE_COLUMN_FORMAT, t->columns[i].type_s, t->columns[i].name);
    }
    fprintf(f, "\n");
    // for (size_t i = 0; i < t->num_rows; i++) {
    //     fprintf(f, TABLE_COLUMN_FORMAT, t->columns[i].type_s,
    //     t->columns[i].name);
    // }
    fclose(f);
    return SUCCESS;
}

enum Result append_table_to_list(struct Table* table) {
    FILE* f = fopen(MAIN_FILE_PATH, "a");
    if (f == NULL) {
        return TABLE_NOT_CREATED;
    }
    // Go to the end of the file
    fseek(f, 0, SEEK_END);

    fprintf(
        f, TABLE_LIST_FORMAT_OUT, table->name, table->num_rows,
        table->num_columns);
    fclose(f);

    return SUCCESS;
}

enum Result create_table(char table_name[]) {
    struct Table new_table = {.num_columns = 1, .num_rows = 0};
    strcpy(new_table.name, table_name);
    struct Column pk_column = {.is_empty = true, .type = UINT};
    puts("Type the name of the primary key column (id, for example):");
    display_user_arrow();
    scanf("%s", pk_column.name);
    fflush(stdin);
    memcpy(&new_table.columns[0], &pk_column, sizeof(pk_column));
    printf("Primary key column [%s] of type [UINT] created!\n", pk_column.name);
    puts("Add columns to your table:");
    while (true) {
        unsigned int type;
        printf(
            "Column type options:\n {1} UINT, {2} INT, {3} FLOAT, {4} DOUBLE, "
            "{5} "
            "CHAR, {6} STRING. Type 0 to leave.\n");
        display_user_arrow();
        scanf(" %u", &type);
        fflush(stdin);
        char type_s[20];
        type_to_string(type, type_s);
        if (type == 0) {
            break;
        }
        if (strcmp(type_s, "unknown") == 0) {
            puts("Not a valid input, please try again");
            continue;
        }
        struct Column* curr_column = &new_table.columns[new_table.num_columns];
        curr_column->type = type;
        strcpy(curr_column->type_s, type_s);
        printf("Type the name of your column of type %s\n", type_s);
        display_user_arrow();
        scanf(" %[^\n]", curr_column->name);
        fflush(stdin);
        curr_column->is_empty = true;
        printf(
            "column [%s] of type [%s] created!\n", curr_column->name, type_s);
        new_table.num_columns++;
    }

    enum Result result = append_table_to_list(&new_table);
    if (result != SUCCESS) return result;
    result = persist_table(&new_table);
    if (result != SUCCESS) return result;
    puts("Table created.");
    return result;
}

void list_tables() {
    char table[MAX_TABLE_NAME_SIZE];
    unsigned int rows, columns;
    FILE* f = fopen(MAIN_FILE_PATH, "r");
    puts("Tables:");
    while (fscanf(f, TABLE_LIST_FORMAT_IN, table, &rows, &columns) != EOF) {
        printf("%s\n", table);
    }
    fclose(f);
}

enum Result delete_table(char table_name[]) {
    char table[MAX_TABLE_NAME_SIZE];
    unsigned int rows, columns;
    delete_table_file(table_name);
    FILE *f, *temp;
    char temp_filename[MAX_PATH_SIZE];
    sprintf(temp_filename, "./db/temp____listoftables.txt");
    f = fopen(MAIN_FILE_PATH, "r");
    temp = fopen(temp_filename, "w");

    if (f == NULL) {
        printf("error\n");
        return ERROR;
    }

    if (temp == NULL) {
        return TABLE_NOT_CREATED;
    }
    while (fscanf(f, TABLE_LIST_FORMAT_IN, table, &rows, &columns) != EOF) {
        if (strcmp(table, table_name) != 0)
            fprintf(temp, TABLE_LIST_FORMAT_OUT, table, rows, columns);
    }

    fclose(f);
    fclose(temp);

    remove(MAIN_FILE_PATH);
    rename(temp_filename, MAIN_FILE_PATH);

    return SUCCESS;
}
int delete_table_file(char table_name[]) {
    sprintf(FILE_PATH, "./db/%s.txt", table_name);
    int r = remove(FILE_PATH);
    return r;
}

int table_already_exists(char table_name[]) {
    FILE* f = fopen(MAIN_FILE_PATH, "r");
    char name[MAX_TABLE_NAME_SIZE];
    while (fscanf(f, "%s\n", name) != EOF) {
        if (strcmp(name, table_name) == 0) {
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void get_table_info(char table_name[], struct Table* t) {
    FILE* f = fopen(MAIN_FILE_PATH, "r");
    char name[MAX_TABLE_NAME_SIZE];
    unsigned int num_rows, num_columns;
    while (fscanf(f, "%s %u %u\n", name, &num_rows, &num_columns) != EOF) {
        if (strcmp(name, table_name) == 0) {
            strcpy(t->name, name);
            t->num_rows = num_rows;
            t->num_columns = num_columns;
        }
    }
    fclose(f);
}

enum Result add_data(char table_name[]) {
    sprintf(FILE_PATH, "./db/%s.txt", table_name);
    // 1- Carrega as colunas da tabela
    //  2- Pede os dados de cada tabela
    //  3- Se pk ja estiver em uso, retorna erro e impede persistencia de
    //  registro

    struct Table t;
    get_table_info(table_name, &t);
}

enum Result delete_data(char table_name[], unsigned int pk) {
    // 1- Dado um nome de tabela e primary key -> Delete o registro daquela pk
    //  2- Se não existir um registro com aquela primary key -> Retorna erro
    //  para o usuário
    struct Table t;
    get_table_info(table_name, &t);
    if (t.num_rows == 0) {
        printf("table %s has no data to delete\n", table_name);
        return ERROR;
    }
    return SUCCESS;
}
