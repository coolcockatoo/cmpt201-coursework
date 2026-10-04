#include <stdio.h>
#include <string.h>

int main(void) {
  char lines[5][256];
  int count = 0;

  while (fgets(lines[count % 5], 256, stdin) != NULL) {
    lines[count % 5][strcspn(lines[count % 5], "\r\n")] = '\0';

    if (strcmp(lines[count % 5], "print") == 0) {
      count++;
      int total = (count < 5) ? count : 5;
      int start = (count < 5) ? 0 : (count % 5);

      for (int i = 0; i < total; i++) {
        printf("%s\n", lines[(start + i) % 5]);
      }
    } else {
      count++;
    }
  }

  return 0;
}
