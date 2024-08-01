#include <stdbool.h>

enum Errors { TABLE_NOT_CREATED = 1 };

/*
 * checks if user input matches with a given command
 */
bool check_command(const char input[], const char command[]);
