#include <stdbool.h> 
#include <stdio.h>
#include <string.h>

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
            puts("Type the name of the table to create:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);
            if (table_already_exists(user_input)) {
                printf("Table with name \"%s\" already exists\n", user_input);
                continue;
            }
            enum Result has_err = create_table(user_input);
            if (has_err != SUCCESS) {
                printf("Table %s was not created!\n", user_input);
                continue;
            }
            printf("Table %s created succesfully!\n", user_input);
        }
        else if (check_command(user_input, "list")) {
            list_tables();
            continue;
        }
        else if (check_command(user_input, "search")) {
            continue;
        }
        else if (check_command(user_input, "add")) {
            list_tables();
            puts("Type the name of the table that you want to add data to:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
            format_name(user_input);
            if (!table_already_exists(user_input)) {
                printf("Table with name \"%s\" doesn't exists!\n", user_input);
                continue;
            }
            enum Result has_err = add_data(user_input);
            if (has_err != SUCCESS) {
                printf("Could not add data to table %s\n", user_input);
                continue;
            }
            printf("Your data was registered in table %s", user_input);
            continue;
        }
        else if (check_command(user_input, "delete")) {
            list_tables();
            puts("Type the name of the table you want to delete:");
            display_user_arrow();
            scanf(" %[^\n]", user_input);
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
