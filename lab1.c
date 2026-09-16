#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  printf("Enter text to tokenize (Press Enter on an empty line to exit):\n");

  while (1) {
    printf("> ");
    fflush(stdout);

    ssize_t nread = getline(&line, &cap, stdin);

    // Exit on EOF (Ctrl+D) or read error
    if (nread == -1) {
      break;
    }

    // Exit if the user pressed Enter on an empty line
    if (nread == 1 && line[0] == '\n') {
      printf("Exiting program.\n");
      break;
    }

    // Strip the trailing newline character
    if (nread > 0 && line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    // Tokenize using strtok_r with " " (space) delimiter
    char *saveptr;
    char *str = line;
    char *token;

    while ((token = strtok_r(str, " ", &saveptr)) != NULL) {
      printf("%s\n", token);
      str = NULL;
    }
  }

  free(line);
  return 0;
}
