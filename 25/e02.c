#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 100
#define BUFSIZE 10000
#define NUM "02"

long part1(char *input) {
  long result = 0;
  char *token = strtok(input, "-,");
  while (token != NULL) {
    long start = atol(token);
    char *endStr = strtok(NULL, "-,");
    long end = atol(endStr);
    for (long i = start; i <= end; i++) {
      char numStr[STRSIZE];
      sprintf(numStr, "%ld", i);
      int numLen = strlen(numStr);

      if (numLen % 2 == 0 && strstr(numStr, numStr + numLen / 2) == numStr) {
        result += i;
      }
    }
    token = strtok(NULL, "-,");
  }
  return result;
}

long part2(char *input) {
  long result = 0;
  char *token = strtok(input, ",-");
  while (token != NULL) {
    long start = atol(token);
    char *endStr = strtok(NULL, "-,");
    long end = atol(endStr);
    for (long i = start; i <= end; i++) {
      char numStr[STRSIZE / 2];
      sprintf(numStr, "%ld", i);
      if (i / 100 < 1) {
        if (numStr[0] == numStr[1]) {
          result += i;
        }
        continue;
      }

      char buf[STRSIZE];
      sprintf(buf, "%s%s", numStr, numStr);
      char *subsPos = strstr(buf + 1, numStr);
      if (subsPos != NULL && buf + strlen(numStr) != subsPos) {
        result += i;
      }
    }
    token = strtok(NULL, ",-");
  }
  return result;
}

int main(int argc, char *argv[]) {
  char *filename = argc > 1 ? argv[1] : "e" NUM "-input.txt";

  FILE *file = fopen(filename, "r");
  assert(file && "Error opening file");

  char buffer[BUFSIZE];
  if (fgets(buffer, sizeof(buffer), file) == NULL) {
    fclose(file);
    assert(0 && "Error reading file");
  }
  fclose(file);
  char *input = calloc(strlen(buffer), sizeof(char));
  strcpy(input, buffer);
  long result1 = part1(input);
  strcpy(input, buffer);
  long result2 = part2(input);
  free(input);

  printf("PART 1: %ld\n", result1);
  printf("PART 2: %ld\n", result2);

  return 0;
}
