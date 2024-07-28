#include "messages.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
int main() {

  char user_input[256];

  display_menu_message();
  while (true) {
    fgets(user_input, 256, stdin);

    if (user_input[0] == '\n') {
      continue;
    }

    user_input[strlen(user_input) - 1] = '\0';

    if (check_command(user_input, "help")) {
      display_help_message();
      continue;
    } else if (check_command(user_input, "leave")) {
      break;
    }
  }

  display_ending_message();

  return 0;
}
