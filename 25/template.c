#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM "01"

int part1(char **lines, size_t lineCount) {
  return 0;
};

int part2(char **lines, size_t lineCount) {
  return 0;
};

int main(int argc, char *argv[]) {
  char *filename = argc > 1 ? argv[1] : "e" NUM "-input.txt";

  char **lines = NULL;
  int lineCount = readLinesFromFile(filename, &lines);

  int result1 = part1(lines, lineCount);
  int result2 = part2(lines, lineCount);
  freeLines(lines, lineCount);

  printf("PART 1: %d\n", result1);
  printf("PART 2: %d\n", result2);

  return 0;
}
