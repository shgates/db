#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "messages.h"
#include "table.h"
#include "utils.h"

#define MAX_USER_INPUT 512

int main() {
    display_menu_message();
    char user_input[MAX_USER_INPUT];

    while (true) {
        display_user_arrow();
        fgets(user_input, MAX_USER_INPUT, stdin);

        if (user_input[0] == '\n') {
            continue;
        }

        user_input[strlen(user_input) - 1] = '\0';

        if (check_command(user_input, "help")) {
            display_help_message();
        }
        else if (
            check_command(user_input, "quit") ||
            check_command(user_input, "exit") || user_input[0] == 'q') {
            display_ending_message();
            break;
        }
        else if (check_command(user_input, "credits")) {
            display_credits_message();
        }
        else if (check_command(user_input, "create")) {
            list_tables();
            puts("Digite o nome da tabela que você quer criar:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);
            if (table_already_exists(user_input)) {
                printf("Uma tabela com nome \"%s\" já existe!\n", user_input);
                continue;
            }
            enum Result has_err = create_table(user_input);
            if (has_err != SUCCESS) {
                printf("Tabela %s não foi criada!\n", user_input);
                continue;
            }
            printf("Tabela %s criada com sucesso!\n", user_input);
        }
        else if (check_command(user_input, "list")) {
            list_tables();

            puts(
                "Digite o nome de uma tabela para ler seu conteúdo ou digite "
                "'quit' para sair");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            if (check_command(user_input, "quit")) {
                puts("Voltando para o menu inicial!");
                continue;
            }
            format_name(user_input);

            if (!table_already_exists(user_input)) {
                printf("Tabela com nome \"%s\" não existe!\n", user_input);
                continue;
            }

            list_data(user_input);
        }
        else if (check_command(user_input, "search")) {
            list_tables();
            puts("Informe o nome da tabela que você quer fazer a pesquisa");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);

            if (!table_already_exists(user_input)) {
                printf("Tabela com nome \"%s\" não existe!\n", user_input);
                continue;
            }

            char value[MAX_USER_INPUT];
            struct Table t;
            get_table_info(user_input, &t);

            char col_name[MAX_USER_INPUT];
            bool quit = false;
            while (true) {
                puts(
                    "Informe o nome da coluna ou digite 'quit' para sair da "
                    "busca");
                for (size_t i = 0; i < t.num_columns; i++) {
                    printf("%s\n", t.columns[i].name);
                }
                display_user_arrow();
                scanf(" %[^\n]", col_name);
                if (check_command(col_name, "quit")) {
                    quit = true;
                    break;
                }
                if (column_exist(col_name, t)) {
                    break;
                }
                else {
                    printf(
                        "Coluna %s não existe em tabela %s\n", col_name,
                        t.name);
                }
            }
            if (quit) {
                puts("Voltando para o menu inicial!");
                continue;
            }
            puts(
                "Selecione se quer fazer uma comparação numérica ou buscar "
                "um "
                "texto:");
            puts("1 -> Comparação numérica");
            puts("2 -> Buscar texto");
            int option;
            display_user_arrow();
            scanf(" %d", &option);
            if (option == 2) {
                // Busca de texto não foi implementada
                puts(
                    "Sinto muito, mas a ferramenta de busca de texto não está "
                    "pronta!");
                continue;
            }
            puts("Digite o valor:");
            display_user_arrow();
            scanf(" %[^\n]", value);
            switch (option) {
                case 1:
                    if (!is_number(value)) {
                        puts("Valor não é um número");
                        continue;
                    }

                    break;
                case 2:
                    // Não é necessário validação
                    break;

                default:
                    puts("Escolha não existe");
                    continue;
            }
            enum Result result = search_data(user_input, col_name, value, t);
            if (result != SUCCESS) {
                puts("Busca não foi realizada");
            }
        }
        else if (check_command(user_input, "add")) {
            list_tables();
            puts(
                "Digite o nome da tabela que você quer adicionar um novo "
                "registro:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);
            if (!table_already_exists(user_input)) {
                printf("Tabela com nome \"%s\" não existe!\n", user_input);
                continue;
            }
            enum Result has_err = add_data(user_input);
            if (has_err == ERROR_PRIMARY_KEY_EXISTS) {
                printf("Um registro com essa chave primária já existe");
                continue;
            }
            if (has_err != SUCCESS) {
                printf(
                    "Não foi possível adicionar registro à tabela %s\n",
                    user_input);
                continue;
            }
            printf(
                "Seu registro foi adicionado na tabela %s com sucesso!",
                user_input);
        }
        else if (check_command(user_input, "remove")) {
            list_tables();
            puts("Digite a tabela que você remover um registro");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);

            if (!table_already_exists(user_input)) {
                printf("Tabela com nome \"%s\" não existe!\n", user_input);
                continue;
            }

            list_data(user_input);
            unsigned int pk;
            puts("Digite a chave primária do registro que você quer remover");
            display_user_arrow();
            scanf(" %u", &pk);
            enum Result result = delete_data(user_input, pk);
            if (result == ERROR_PRIMARY_KEY_NOT_EXISTS) {
                printf("Chave primária %u não existe nessa tabela\n", pk);
                continue;
            }
            else if (result != SUCCESS) {
                printf(
                    "Não foi possível deletar registro na tabela %s\n",
                    user_input);
                continue;
            }

            puts("Registro deletado com sucesso");
        }
        else if (check_command(user_input, "delete")) {
            list_tables();
            puts("Digite o nome da tabela que você quer deletar:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);
            if (!table_already_exists(user_input)) {
                printf("Tabela com nome \"%s\" não existe\n", user_input);
                continue;
            }
            enum Result has_err = delete_table(user_input);
            if (has_err != SUCCESS) {
                printf("Tabela %s não existe!\n", user_input);
                continue;
            }
            printf("Tabela %s foi deletada com sucesso!\n", user_input);
            continue;
        }
        else {
            display_invalid_input_message();
        }
    }

    return 0;
}
