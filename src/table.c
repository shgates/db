
#include "table.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "messages.h"
#include "utils.h"

#define MAX_PATH_SIZE 1000
#define MAX_TABLE_QUANTITY 100
#define MAX_TABLE_NAME_SIZE 100
#define MAX_INPUT 1024

// Formatação de entrada (ex: fscanf) do arquivo listoftables
// (Nome, Numero de linhas, Numero de Colunas)
const char* TABLE_LIST_FORMAT_IN = "%s %u %u\n";

// Formatação de saida (ex: fprintf) do arquivo listoftables
// (Nome, Numero de linhas, Numero de Colunas)
const char* TABLE_LIST_FORMAT_OUT = "%s %u %u\n";

// Formatação de uma coluna de tabela
const char* TABLE_COLUMN_FORMAT = "%s %s|";

// Formatação de entrada (ex: fscanf) de um registro de uma tabela
const char* TABLE_ROW_FORMAT_IN = "%[^|]";
// Formatação de saida (ex: fprintf) de um registro de uma tabela
const char* TABLE_ROW_FORMAT_OUT = "%s|";

// Variável buffer para manipular o caminho de uma tabela (Sem ser o arquivo
// listoftables.txt)
static char FILE_PATH[MAX_PATH_SIZE];

// Caminho do txt principal contendo dados sobre nome, numero de linhas e numero
// de colunas de cada tabela do db
static char MAIN_FILE_PATH[] = "./db/listoftables.txt";

// Função usada para ler as colunas de uma tabela depois de ter lido as colunas
// em um txt Parametros da função: t - ponteiro para uma variavel de tipo Table
// buffer_line - a string contendo as colunas de uma tabela (Pega usando fgets)
// num_columns - quantidade de colunas dessa tabela
void get_columns(struct Table* t, char* buffer_line, unsigned int num_columns) {
    size_t line_index = 0, count = 0;
    for (size_t i = 0; i < num_columns; i++) {
        char name[256], type_s[256];
        // Copia o tipo da coluna (em texto)
        while (buffer_line[line_index] != ' ') {
            type_s[count] = buffer_line[line_index];
            count++;
            line_index++;
        }

        type_s[count++] = '\0';

        strcpy(t->columns[i].type_s, type_s);
        printf("");
        t->columns[i].type = string_to_type(type_s);
        // Pula o espaço
        line_index++;
        // Reseta contador
        count = 0;
        // Copia nome da coluna
        while (buffer_line[line_index] != '|') {
            name[count] = buffer_line[line_index];
            count++;
            line_index++;
        }
        // Formata o texto
        name[count++] = '\0';

        strcpy(t->columns[i].name, name);
        // Pula a barra
        line_index++;
        // Reseta contador
        count = 0;
        memset(name, 0, 256);
        memset(type_s, 0, 256);
    }
}

// função usada para persistir uma tabela nova -> Usado dentro da função
// create_table
enum Result persist_table(struct Table* t) {
    sprintf(FILE_PATH, "./db/%s.txt", t->name);
    FILE* f = fopen(FILE_PATH, "w");
    if (f == NULL) {
        printf("Um erro ocorreu ao tentar criar a tabela %s.\n", t->name);
        return ERROR;
    }
    fprintf(f, TABLE_COLUMN_FORMAT, "uint", t->columns[0].name);

    for (size_t i = 1; i < t->num_columns; i++) {
        fprintf(
            f, TABLE_COLUMN_FORMAT, t->columns[i].type_s, t->columns[i].name);
    }
    fprintf(f, "\n");
    fclose(f);
    return SUCCESS;
}

// Adiciona a nova tabela ao txt "listoftables"
// Função usada em create_table
enum Result append_table_to_list(struct Table* table) {
    FILE* f = fopen(MAIN_FILE_PATH, "a");
    if (f == NULL) {
        return ERROR_TABLE_NOT_CREATED;
    }
    // Vai para o final do txt
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
    struct Column pk_column = {.type = UINT};
    puts("Digite o nome da coluna da primary key (id, por exemplo):");
    display_user_arrow();
    scanf("%s", pk_column.name);
    fflush(stdin);
    memcpy(&new_table.columns[0], &pk_column, sizeof(pk_column));
    printf("Coluna Primary Key [%s] de tipo [UINT] criada!\n", pk_column.name);
    puts("Adicione colunas para a sua tabela:");
    while (true) {
        unsigned int type;
        printf(
            "Opções de tipo para coluna:\n {1} UINT, {2} INT, {3} FLOAT, {4} "
            "DOUBLE, "
            "{5} "
            "CHAR, {6} STRING. Digite 0 para sair.\n");
        display_user_arrow();
        scanf(" %u", &type);
        fflush(stdin);
        char type_s[20];
        type_to_string(type, type_s);
        if (type == 0) {
            break;
        }
        if (strcmp(type_s, "unknown") == 0) {
            puts("Não é um input válido, por favor tente novamente");
            continue;
        }
        struct Column* curr_column = &new_table.columns[new_table.num_columns];
        curr_column->type = type;
        strcpy(curr_column->type_s, type_s);
        printf("Digite o nome para a sua coluna do tipo [%s]\n", type_s);
        display_user_arrow();
        scanf(" %[^\n]", curr_column->name);
        fflush(stdin);
        printf("coluna [%s] de tipo [%s] criada!\n", curr_column->name, type_s);
        new_table.num_columns++;
    }

    enum Result result = append_table_to_list(&new_table);
    if (result != SUCCESS) return result;
    result = persist_table(&new_table);
    if (result != SUCCESS) return result;
    return result;
}

void list_tables() {
    char table[MAX_TABLE_NAME_SIZE];
    unsigned int rows, columns;
    FILE* f = fopen(MAIN_FILE_PATH, "r");
    puts("Tabelas:");
    while (fscanf(f, TABLE_LIST_FORMAT_IN, table, &rows, &columns) != EOF) {
        printf("%s\n", table);
    }
    printf("\n");
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
        return ERROR;
    }
    while (fscanf(f, TABLE_LIST_FORMAT_IN, table, &rows, &columns) != EOF) {
        if (strcmp(table, table_name) != 0) {
            fprintf(temp, TABLE_LIST_FORMAT_OUT, table, rows, columns);
        }
    }

    fclose(f);
    fclose(temp);

    remove(MAIN_FILE_PATH);
    rename(temp_filename, MAIN_FILE_PATH);

    return SUCCESS;
}

// Deleta txt contendo dados da tabela (Coluna e registros)
int delete_table_file(char table_name[]) {
    sprintf(FILE_PATH, "./db/%s.txt", table_name);
    int r = remove(FILE_PATH);
    return r;
}

// Checa se uma tabela existe
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

// Função que recebe nome da tabela e ponteiro para uma variavel de tipo Table
// e retorna os dados da tabela para o ponteiro
enum Result get_table_info(char table_name[], struct Table* t) {
    FILE* f = fopen(MAIN_FILE_PATH, "r");
    if (f == NULL) return ERROR;
    char name[MAX_TABLE_NAME_SIZE];
    unsigned int num_rows, num_columns;
    bool found = false;
    while (fscanf(f, TABLE_LIST_FORMAT_IN, name, &num_rows, &num_columns) !=
           EOF) {
        if (strcmp(name, table_name) == 0) {
            found = true;
            // Copia a quantidade de linhas e colunas da tabela
            strcpy(t->name, name);
            t->num_rows = num_rows;
            t->num_columns = num_columns;

            // Copia os dados da tabela
            sprintf(FILE_PATH, "./db/%s.txt", table_name);
            FILE* fp = fopen(FILE_PATH, "r");
            if (fp == NULL) return ERROR;
            // Copia as colunas
            char buffer[2048];
            fgets(buffer, 2048, fp);
            get_columns(t, buffer, t->num_columns);

            // Copia os registros
            char data[t->num_columns][100];
            for (size_t i = 0; i < t->num_rows; i++) {
                for (size_t j = 0; j < t->num_columns; j++) {
                    // Le registro de uma coluna
                    fscanf(fp, TABLE_ROW_FORMAT_IN, data[j]);
                    // Pula a barra
                    fseek(fp, 1, SEEK_CUR);
                    switch (t->columns[j].type) {
                        case UINT:
                            t->columns[j].data_uint[i] = atoi(data[j]);
                            break;
                        case INT:
                            t->columns[j].data_int[i] = atoi(data[j]);
                            break;
                        case FLOAT:
                            t->columns[j].data_float[i] = atof(data[j]);
                            break;
                        case DOUBLE:
                            t->columns[j].data_double[i] = atof(data[j]);
                            break;
                        case CHAR:
                            t->columns[j].data_char[i] = data[j][0];
                            break;
                        case STRING:
                            strcpy(t->columns[j].data_string[i], data[j]);
                            break;
                    }
                }
            }
            fclose(fp);
        }
    }
    fclose(f);
    if (found == false) return ERROR_TABLE_NOT_FOUND;
    return SUCCESS;
}

enum Result add_data(char table_name[]) {
    sprintf(FILE_PATH, "./db/%s.txt", table_name);
    // 1- Carrega as colunas da tabela
    //  2- Pede os dados de cada tabela
    //  3- Se pk ja estiver em uso, retorna erro e impede persistencia de
    //  registro

    struct Table t;
    enum Result result = get_table_info(table_name, &t);
    if (result != SUCCESS) {
        printf("Não foi possivel carregar dados da tabela %s\n", table_name);
        return ERROR;
    }
    printf("Tabela %s\n\n:", table_name);
    for (size_t i = 0; i < t.num_columns; i++) {
        printf("[%s] %s | ", t.columns[i].type_s, t.columns[i].name);
    }
    printf("\n");
    for (size_t i = 0; i < t.num_rows; i++) {
        for (size_t j = 0; j < t.num_columns; j++) {
            print_data(t.columns[j], t.columns[j].type, i);
        }
        printf("\n");
    }
    printf("\n");
    char new_data[t.num_columns][100];
    FILE* f = fopen(FILE_PATH, "a+");
    if (f == NULL) return ERROR;

    fseek(f, 0, SEEK_END);
    for (size_t i = 0; i < t.num_columns; i++) {
        printf(
            "Adicione dados para coluna [%s] %s", t.columns[i].type_s,
            t.columns[i].name);
        display_user_arrow();
        scanf(" %s", new_data[i]);
        fflush(stdin);
    }

    unsigned int pk = atoi(new_data[0]);
    // Checa se primary key é positivo
    if (pk > INT_MAX || pk == 0) {
        printf("Chave primária deve ser um número positivo\n");
        return ERROR;
    }
    // Checa se primary key já existe
    if (primary_key_exists(&t, pk)) {
        return ERROR_PRIMARY_KEY_EXISTS;
    }

    for (size_t i = 0; i < t.num_columns; i++) {
        fprintf(f, TABLE_ROW_FORMAT_OUT, new_data[i]);
    }
    fprintf(f, "\n");
    fclose(f);

    t.num_rows++;
    update_table_row(&t);
    return SUCCESS;
}

enum Result delete_data(char table_name[], unsigned int pk) {
    // 1- Dado um nome de tabela e primary key -> Delete o registro daquela pk
    //  2- Se não existir um registro com aquela primary key -> Retorna erro
    //  para o usuário
    struct Table t;
    enum Result result = get_table_info(table_name, &t);
    if (result != SUCCESS) {
        printf("Não foi possivel carregar dados da tabela %s\n", table_name);
        return ERROR;
    }
    if (t.num_rows == 0) {
        printf("Tabela %s não possui dados para deletar\n", table_name);
        return ERROR;
    }
    if (!primary_key_exists(&t, pk)) {
        return ERROR_PRIMARY_KEY_NOT_EXISTS;
    }
    FILE *file, *temp;
    char temp_filename[MAX_PATH_SIZE];
    sprintf(FILE_PATH, "./db/%s.txt", table_name);
    sprintf(temp_filename, "./db/temp____%s.txt", table_name);
    file = fopen(FILE_PATH, "r");
    temp = fopen(temp_filename, "w");

    if (file == NULL || temp == NULL) {
        return ERROR;
    }

    // Copia as colunas das tabelas para o novo arquivo
    char line[2048];
    fgets(line, 2048, file);
    fputs(line, temp);

    // Copia os registros das tabelas para o novo arquivo
    // com exceção do registro com a pk selecionada
    for (size_t i = 0; i < t.num_rows; i++) {
        fgets(line, 2048, file);
        if (pk != t.columns[0].data_uint[i]) {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_PATH);
    rename(temp_filename, FILE_PATH);

    t.num_rows--;
    update_table_row(&t);

    return SUCCESS;
}

void print_data(struct Column col, enum Type type, size_t idx) {
    int padding = 5;
    switch (type) {
        case UINT:
            printf("%*u", padding, col.data_uint[idx]);
            break;
        case INT:
            printf("%*d", padding, col.data_int[idx]);
            break;
        case FLOAT:
            printf("%*.2f", padding, col.data_float[idx]);
            break;
        case DOUBLE:
            printf("%*.2lf", padding, col.data_double[idx]);
            break;
        case CHAR:
            printf("%*c", padding, col.data_char[idx]);
            break;
        case STRING:
            printf("%*s", padding, col.data_string[idx]);
            break;
    }
    printf("%*c", padding, '|');
}

enum Result update_table_row(struct Table* t) {
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
        return ERROR_TABLE_NOT_UPDATED;
    }
    char table_buffer[MAX_TABLE_NAME_SIZE];
    unsigned int rows, columns;
    while (fscanf(f, TABLE_LIST_FORMAT_IN, table_buffer, &rows, &columns) !=
           EOF) {
        if (strcmp(table_buffer, t->name) != 0)
            fprintf(temp, TABLE_LIST_FORMAT_OUT, table_buffer, rows, columns);
        else {
            fprintf(
                temp, TABLE_LIST_FORMAT_OUT, t->name, t->num_rows,
                t->num_columns);
        }
    }

    fclose(f);
    fclose(temp);

    remove(MAIN_FILE_PATH);
    rename(temp_filename, MAIN_FILE_PATH);
    return SUCCESS;
}

enum Result list_data(char table_name[]) {
    sprintf(FILE_PATH, "./db/%s.txt", table_name);

    FILE* file = fopen(FILE_PATH, "r");

    if (file == NULL) {
        printf("Erro ao ler tabela %s", table_name);
        return ERROR;
    }

    char* table_data = malloc(sizeof(char) * MAX_INPUT);  // Reservando Vetor.

    printf("\nDados da tabela %s\n\n", table_name);

    while (fgets(table_data, (MAX_INPUT + 1), file)) {
        printf("%s", table_data);
        memset(table_data, 0, MAX_INPUT + 1);  // Limpando o conteúdo da matriz
    }
    free(table_data);  // Liberando a memória alocada após o loop
    fclose(file);      // Fechando o arquivo
    return SUCCESS;
}

enum Result search_data(
    char table_name[], char col_name[], char value[], struct Table t) {
    double num_value = atof(value);

    int col_idx = 0;
    for (size_t i = 0; i < t.num_columns; i++) {
        if (strcmp(col_name, t.columns[i].name) == 0) {
            col_idx = i;
        }
    }
    int option;
    while (true) {
        puts("Selecione a opção de pesquisa:");
        puts("{1} -> Valores maior que o informado");
        puts("{2} -> Valores maior ou igual que o informado");
        puts("{3} -> Valores iguais que o informado");
        puts("{4} -> Valores menor que o informado");
        puts("{5} -> Valores maior ou igual que o informado");

        display_user_arrow();
        scanf("%d", &option);

        if (option >= 1 && option <= 5) {
            break;
        }
    }

    double col_values[t.num_columns];

    get_numerical_values(t.columns[col_idx], t.num_rows, col_values);

    int c = 0;
    int rows[t.num_rows];
    switch (option) {
        case 1:
            for (size_t i = 0; i < t.num_rows; i++) {
                if (col_values[i] > num_value) {
                    rows[c] = i;
                    c++;
                }
            }
            break;
        case 2:
            for (size_t i = 0; i < t.num_rows; i++) {
                if (col_values[i] >= num_value) {
                    rows[c] = i;
                    c++;
                }
            }
            break;
        case 3:
            for (size_t i = 0; i < t.num_rows; i++) {
                if (col_values[i] == num_value) {
                    rows[c] = i;
                    c++;
                }
            }
            break;
        case 4:
            for (size_t i = 0; i < t.num_rows; i++) {
                if (col_values[i] < num_value) {
                    rows[c] = i;
                    c++;
                }
            }
            break;
        case 5:
            for (size_t i = 0; i < t.num_rows; i++) {
                if (col_values[i] <= num_value) {
                    rows[c] = i;
                    c++;
                }
            }
            break;
    }

    // printa tabela

    sprintf(FILE_PATH, "./db/%s.txt", table_name);

    FILE* file = fopen(FILE_PATH, "r");

    if (file == NULL) {
        printf("Erro ao ler tabela %s", table_name);
        return ERROR;
    }

    char* table_data = malloc(sizeof(char) * MAX_INPUT);

    printf("\nDados da tabela %s\n\n", table_name);

    int count = 0;
    while (fgets(table_data, (MAX_INPUT + 1), file)) {
        if (count == 0 || array_contains_idx(rows, c, count - 1)) {
            printf("%s", table_data);
            memset(table_data, 0, MAX_INPUT + 1);
        }
        count++;
    }
    free(table_data);
    fclose(file);

    return SUCCESS;
}

bool primary_key_exists(struct Table* t, unsigned int pk) {
    for (size_t i = 0; i < t->num_rows; i++) {
        if (pk == t->columns[0].data_uint[i]) {
            return true;
        }
    }
    return false;
}

bool column_exist(char column_name[], struct Table t) {
    for (size_t i = 0; i < t.num_columns; i++) {
        if (strcmp(t.columns[i].name, column_name) == 0) {
            return true;
        }
    }
    return false;
}

void get_numerical_values(
    struct Column col, unsigned int num_rows, double* data) {
    if (col.type == UINT) {
        for (size_t i = 0; i < num_rows; i++) {
            data[i] = (double)col.data_uint[i];
        }
    }
    else if (col.type == INT) {
        for (size_t i = 0; i < num_rows; i++) {
            data[i] = (double)col.data_int[i];
        }
    }
    else if (col.type == FLOAT) {
        for (size_t i = 0; i < num_rows; i++) {
            data[i] = (double)col.data_float[i];
        }
    }
    else if (col.type == DOUBLE) {
        for (size_t i = 0; i < num_rows; i++) {
            data[i] = col.data_double[i];
        }
    }
}
