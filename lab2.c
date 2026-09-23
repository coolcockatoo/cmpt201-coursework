#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char input_path[1024];

  while (1) {
    printf("> ");
    fflush(stdout);

    if (fgets(input_path, sizeof(input_path), stdin) == NULL) {
      break;
    }

    input_path[strcspn(input_path, "\n")] = '\0';

    if (strlen(input_path) == 0) {
      continue;
    }

    pid_t pid = fork();

    if (pid == 0) {
      execl(input_path, input_path, NULL);
      perror("Execution failed");
      return 1;
    } else if (pid > 0) {
      waitpid(pid, NULL, 0);
    }
  }

  return 0;
}
