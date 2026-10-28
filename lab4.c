#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

int main() {
  void *heap_start = sbrk(256);

  if (heap_start == (void *)-1) {
    perror("sbrk failed");
    return 1;
  }

  char *bytes = heap_start;

  struct header *block1 = (struct header *)bytes;
  struct header *block2 = (struct header *)(bytes + 128);

  block1->size = 128;
  block1->next = block2;

  block2->size = 128;
  block2->next = NULL;

  char *data1 = (char *)block1 + sizeof(struct header);
  memset(data1, 0, 112);

  char *data2 = (char *)block2 + sizeof(struct header);
  memset(data2, 1, 112);

  printf("Block 1 Address: %p\n", (void *)block1);
  printf("Block 2 Address: %p\n", (void *)block2);

  printf("Block 1 Header -> Size: %lu, Next: %p\n", block1->size, (void *)block1->next);
  printf("Block 2 Header -> Size: %lu, Next: %p\n", block2->size, (void *)block2->next);

  printf("Block 1 Data (first byte): %d\n", data1[0]);
  printf("Block 2 Data (first byte): %d\n", data2[0]);

  return 0;
}
