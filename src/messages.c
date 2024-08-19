#include <stdio.h>

/* PIPOCA COM SAL */

void display_user_arrow() { printf("\n»» "); }

void display_menu_message() {
    puts("Bem vindo ao ITP-DB!");
    puts("");
    puts("Digite 'help' para obter ajuda");
}

void display_ending_message() { puts("Encerrando o programa!"); }

void display_help_message() {
    printf("%35s", " Lista de comandos:\n\n");

    printf("%12s: ", "help");
    puts("Mostra a lista de comandos");

    printf("%19s: ", "exit|quit|q");
    puts("Encerra o programa");

    printf("%15s: ", "credits");
    puts("Mostra os criadores do programa");

    puts("");

    printf("%12s: ", "list");
    puts("Lista tabelas e seus dados");

    printf("%14s: ", "search");
    puts("Busca dados dentro de uma tabela");

    puts("");

    printf("%14s: ", "create");
    puts("Cria uma tabela");

    printf("%11s: ", "add");
    puts("Cria um registro em uma tabela");

    printf("%14s: ", "remove");
    puts("Remove um regitro de uma tabela");

    printf("%14s: ", "delete");
    puts("Deleta uma tabela do banco de dados");
}

void display_invalid_input_message() {
    puts("Input inválido, por favor tente novamente.");
}

void display_credits_message() {
    puts("Feito por Felipe Barauna e Alison Soares");
}
