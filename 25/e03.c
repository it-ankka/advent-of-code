#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0
#define DAY "03"
#define FILENAME TEST ? "e" DAY "-test.txt" : "e" DAY "-input.txt"

#define BUFSIZE 1024

long getMaxChar(char *str, int start, int end, char *maxChar) {
  char curMax = '0';
  int idx = start;
  for (int i = start; i < end; i++) {
    if (str[i] > curMax) {
      idx = i;
      curMax = str[i];
    }
  }
  *maxChar = (char)curMax;
  return idx;
}

long getBest(char *str, int k) {
  int start = 0;
  char *nums = calloc(k + 1, sizeof(char));
  for (int i = k; i > 0; i--) {
    int end = strlen(str) - i + 1;
    char maxChar = 0;
    start = getMaxChar(str, start, end - 1, &maxChar) + 1;
    nums[k - i] = maxChar;
  }
  long num = atol(nums);
  free(nums);
  return num;
}

int main(int argc, char *argv[]) {
  char *filename = FILENAME;

  FILE *file = fopen(filename, "r");
  assert(file && "Error opening file");
  char buffer[BUFSIZE];
  long r1 = 0;
  long r2 = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    r1 += getBest(buffer, 2);
    r2 += getBest(buffer, 12);
  }
  fclose(file);

  printf("%ld\n", r1);
  printf("%ld\n", r2);

  return 0;
}
