#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  printf("Enter text to tokenize (Press enter to exit):\n");

  // Loop continuously to accept user input until EOF (Ctrl+D)
  while (1) {
    printf("> ");
    fflush(stdout);

    // Read a line from stdin
    ssize_t nread = getline(&line, &cap, stdin);

    // Handle end-of-file (Ctrl+D) or read failure
    if (nread == -1) {
      break;
    }

    if (nread == 1 && line[0] == '\n') {
      printf("Exiting program.\n");
      break;
    }

    // Strip the trailing newline character added by getline()
    if (nread > 0 && line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    // Tokenize using strtok_r with " " (space) delimiter
    char *saveptr;
    char *str = line;
    char *token;

    while ((token = strtok_r(str, " ", &saveptr)) != NULL) {
      printf("%s\n", token);
      str = NULL; // Subsequent calls require NULL as the first argument
    }
  }

  // Free allocated memory before exit
  free(line);
  return 0;
}
