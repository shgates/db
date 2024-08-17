#include <stdbool.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "messages.h"
#include "table.h"
#include "utils.h"

int main() {
    display_menu_message();
    char user_input[256];

    while (true) {
        display_user_arrow();
        fgets(user_input, 256, stdin);

        if (user_input[0] == '\n') {
            sleep(1);
            continue;
        }

        user_input[strlen(user_input) - 1] = '\0';


        if (check_command(user_input, "help")) {
            display_help_message();
        }
        else if (
            check_command(user_input, "leave") ||
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
            scanf(" %[^\n]", user_input);
            if (check_command(user_input, "quit")) {
                continue;
            }
            format_name(user_input);

            puts("Listagem de tabelas será feito em breve");
        }
        else if (check_command(user_input, "search")) {
            puts("Busca em tabelas será feita em breve");
            continue;
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
            int num_tables = list_tables_with_count();
            puts("Digite o índice da tabela que você quer deletar");
            scanf(" %[^\n]", user_input);
            int num = get_num_from_user_input(user_input);
            printf("numero input = %d\n", num);
            if (num < 1 || num > num_tables) {
                puts("Não existe uma tabela com esse índice");
            }
            puts("Digite a chave primária do registro que você quer remover");
        }
        else if (check_command(user_input, "delete")) {
            list_tables();
            puts("Digite o nome da tabela que você quer deletar:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);
            if (!table_already_exists(user_input)) {
                printf("Table with name \"%s\" doesn't exists\n", user_input);
                continue;
            }
            enum Result has_err = delete_table(user_input);
            if (has_err != SUCCESS) {
                printf("Table %s doesn't exist!\n", user_input);
                continue;
            }
            printf("Table %s deleted succesfully!\n", user_input);
            continue;
        }
        else {
            display_invalid_input_message();
        }
    }

    return 0;
}
