#include <stdbool.h>
#include <string.h>

bool check_command(const char input[], const char command[]) {
  if (strncmp(input, command, strlen(command)) == 0) {
    return true;
  }
  return false;
}
