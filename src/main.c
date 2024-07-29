#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "messages.h"
#include "utils.h"

int main() {
    display_menu_message();
    char user_input[256];

    while (true) {
        display_user_arrow();
        fgets(user_input, 256, stdin);

        // if there is no input, take the input again
        if (user_input[0] == '\n') {
            continue;
        }

        // replace the '\n' leaved by the fgets with a '\0'
        user_input[strlen(user_input) - 1] = '\0';

        if (check_command(user_input, "help")) {
            display_help_message();
            continue;
        }
        else if (
            check_command(user_input, "leave") ||
            check_command(user_input, "exit") || user_input[0] == 'q') {
            break;
        }
        else if (check_command(user_input, "credits")) {
            display_credits_message();
        }
        else if (check_command(user_input, "create")) {
            continue;
        }
        else if (check_command(user_input, "list")) {
            continue;
        }
        else if (check_command(user_input, "search")) {
            continue;
        }
        else if (check_command(user_input, "delete")) {
            continue;
        }
        else {
            display_invalid_input_message();
        }
    }

    display_ending_message();

    return 0;
}
