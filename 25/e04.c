#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0
#define DAY "04"
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
  char **grid = calloc(MAXLINES, sizeof(char *));
  int h = 0;
  while (h < MAXLINES && fgets(buffer, sizeof(buffer), file)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    grid[h] = calloc(strlen(buffer), sizeof(char));
    strcpy(grid[h], buffer);
    h++;
  }
  fclose(file);
  grid = realloc(grid, h * sizeof(char *));
  int w = strlen(grid[0]);

  int prev = 0;
  int isFirstRound = 1;
  do {
    prev = r2;
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (grid[y][x] != '@')
          continue;

        int adjecent = 0;

        for (int dy = max(0, y - 1); dy <= min(y + 1, h - 1); dy++) {
          for (int dx = max(0, x - 1); dx <= min(x + 1, w - 1); dx++) {
            if ((dx != x || dy != y) &&
                (grid[dy][dx] == '@' || grid[dy][dx] == 'x'))
              adjecent += 1;
            if (adjecent > 3)
              break;
          }
          if (adjecent > 3)
            break;
        }
        if (adjecent < 4) {
          grid[y][x] = 'x';
          if (isFirstRound)
            r1++;
          r2++;
        }
      }
    }
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (grid[y][x] == 'x')
          grid[y][x] = '.';
      }
    }
    isFirstRound = 0;
  } while (r2 != prev);

  for (int i = 0; i < h; i++) {
    free(grid[i]);
  }
  free(grid);

  printf("%ld\n", r1);
  printf("%ld\n", r2);

  return 0;
}
