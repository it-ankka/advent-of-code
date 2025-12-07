#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0
#define DAY "05"
#define FILENAME TEST ? "e" DAY "-test.txt" : "e" DAY "-input.txt"

#define BUFSIZE 1024
#define MAXLINES 10000

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)

int main(int argc, char *argv[]) {
  char *filename = FILENAME;

  FILE *file = fopen(filename, "r");
  assert(file && "Error opening file");
  char buffer[BUFSIZE];
  long r1 = 0;
  long r2 = 0;
  long *rangeStart = calloc(MAXLINES, sizeof(long));
  long *rangeEnd = calloc(MAXLINES, sizeof(long));
  int rangeCount = 0;
  while (rangeCount < MAXLINES && fgets(buffer, sizeof(buffer), file) &&
         strlen(buffer) > 1) {
    char *startStr = strtok(buffer, "-\n");
    char *endStr = strtok(NULL, "-\n");
    long start = atol(startStr);
    long end = atol(endStr);
    rangeStart[rangeCount] = start;
    rangeEnd[rangeCount] = end;
    rangeCount++;
  }
  rangeStart = realloc(rangeStart, rangeCount * sizeof(long));
  rangeEnd = realloc(rangeEnd, rangeCount * sizeof(long));

  while (fgets(buffer, sizeof(buffer), file)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    long num = atol(buffer);
    for (int i = 0; i < rangeCount; i++) {
      if (num >= rangeStart[i] && num <= rangeEnd[i]) {
        r1++;
        break;
      }
    }
  }
  fclose(file);

  int minIdx = 0;
  for (int i = 0; i < rangeCount - 1; i++) {
    minIdx = i;
    for (int j = i + 1; j < rangeCount; j++) {
      if (rangeStart[j] < rangeStart[minIdx]) {
        minIdx = j;
      }
    }

    long tmp = rangeStart[minIdx];
    rangeStart[minIdx] = rangeStart[i];
    rangeStart[i] = tmp;

    tmp = rangeEnd[minIdx];
    rangeEnd[minIdx] = rangeEnd[i];
    rangeEnd[i] = tmp;
  }

  long start = rangeStart[0];
  long end = rangeEnd[0];
  for (int i = 1; i < rangeCount; i++) {
    if (rangeStart[i] > end) {
      r2 += (end + 1) - start;
      start = rangeStart[i];
      end = rangeEnd[i];
    } else {
      long curEnd = rangeEnd[i];
      end = max(curEnd, end);
    }
  }
  r2 += (end + 1) - start;

  free(rangeStart);
  free(rangeEnd);

  printf("%ld\n", r1);
  printf("%ld\n", r2);

  return 0;
}
