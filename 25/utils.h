#ifndef INCLUDE_UTILS

#define INCLUDE_UTILS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10000
#define LSIZE 1028

// FILE READING
static inline int readLinesFromFile(const char *filename, char ***lines) {
  FILE *file = fopen(filename, "r");
  assert(file && "Error opening file");

  *lines = (char **)malloc(MAX_LINES * sizeof(char *));
  assert(*lines && "Memory allocation error");

  int lineCount = 0;
  char buffer[LSIZE];

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    // Remove the newline character if present
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
      buffer[length - 1] = '\0';
    }
    // Copy from buffer to lines
    (*lines)[lineCount] = (char *)malloc((length + 1) * sizeof(char));
    assert((*lines)[lineCount] && "Memory allocation error");
    strcpy((*lines)[lineCount], buffer);

    lineCount++;

    if (lineCount >= MAX_LINES) {
      fclose(file);
      assert(1 == 0 && "Max file lines limit reached");
    }
  }

  fclose(file);
  return lineCount;
}

static inline void freeLines(char **lines, int linesCount) {
  for (int i = 0; i < linesCount; i++) {
    free(lines[i]);
  }
  free(lines);
}

// LOGGING
static inline void printArray(int *a, int len) {
  printf("[ ");
  for (int i = 0; i < len; i++)
    printf("%d, ", a[i]);
  printf("]\n");
}

static inline void printCharArray(char *a, int len) {
  printf("[ ");
  for (int i = 0; i < len; i++)
    printf("%c, ", a[i]);
  printf("]\n");
}

// MATH
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define sig(x) (x > 0 ? 1 : x < 0 ? -1 : 0)

// LISTS
typedef struct {
  void **contents;
  size_t length;
  size_t _contents_size;
} List;

static inline List listInit(size_t size) {
  void **contents = (void **)malloc(size * sizeof(void *));
  return (List){
      .contents = contents,
      .length = 0,
      ._contents_size = size,
  };
}

static inline List listEmpty() { return listInit(10); }

static inline void listAppend(List *list, void *item) {
  if (list->length == list->_contents_size) {
    list->_contents_size *= 2;
    list->contents =
        (void **)realloc(list->contents, list->_contents_size * sizeof(void *));
  }
  list->contents[list->length] = item;
  list->length++;
}

static inline void listSet(List *list, size_t index, void *item) {
  list->contents[index] = item;
}

static inline void *listGet(List list, size_t index) {
  return list.contents[index];
}

static inline void listFree(List list) { free(list.contents); }

// POINT
typedef struct Coord {
  int x;
  int y;
} Coord;

// GRID
typedef struct {
  int w;
  int h;
  char **data;
} Grid;

#define GRID_MAX_W 1024
#define GRID_MAX_H 1024

static Grid *newGrid(int cols, int rows) {
  assert(cols > 0);
  assert(rows > 0);
  char *values = (char *)calloc((cols + 1) * rows, sizeof(char));
  assert(values != NULL);
  char **grid = (char **)malloc(rows * sizeof(char *));
  assert(grid != NULL);
  for (int i = 0; i < rows; ++i) {
    grid[i] = values + i * (cols + 1);
  }
  Grid *g = (Grid *)malloc(sizeof(Grid));
  assert(g != NULL);
  g->h = rows;
  g->w = cols;
  g->data = grid;
  return g;
}

static inline Grid *readGridFromFile(char *filepath) {
  FILE *f = fopen(filepath, "r");
  assert(f != NULL);

  char s[GRID_MAX_W];

  int cols = 0;
  int rows = 0;
  while ((fgets(s, GRID_MAX_W, f)) != NULL) {
    cols = max(cols, strlen(s) - 1);
    rows++;
  }

  int lineLen = cols + 2; // Length with newline and null byte

  rewind(f);

  Grid *g = newGrid(cols, rows);
  int row = 0;
  while ((fgets(s, lineLen, f)) != NULL) {
    for (int i = 0; i < cols; i++) {
      g->data[row][i] = s[i];
    }
    row++;
  }

  fclose(f);
  return g;
}

static inline Coord gridFind(Grid *g, char c) {
  for (int row = 0; row < g->h; row++) {
    for (int col = 0; col < g->w; col++) {
      if (g->data[row][col] == c)
        return (Coord){col, row};
    }
  }
  return (Coord){0, 0};
}

static inline void printGrid(FILE *f, Grid *g, int spacing) {
  for (int i = 0; i < g->h; i++) {
    for (int j = 0; j < g->w; j++) {
      fprintf(f, "%c", g->data[i][j]);
      for (int x = 0; x < spacing; x++)
        fprintf(f, " ");
    }
    fprintf(f, "\n");
  }
}

static inline void freeGrid(Grid *grid) {
  free(*grid->data);
  free(grid->data);
  free(grid);
}

static inline Coord gridPosToAbs(Coord pos, float tilesize) {
  pos.x *= tilesize;
  pos.y *= tilesize;
  return pos;
}

// COMPARING
static inline int cmpIntAsc(const void *aPtr, const void *bPtr) {
  int a = *(int *)aPtr;
  int b = *(int *)bPtr;
  if (a > b)
    return 1;
  else if (a < b)
    return -1;
  return 0;
}

static inline int cmpIntDesc(const void *aPtr, const void *bPtr) {
  int a = *(int *)aPtr;
  int b = *(int *)bPtr;
  if (a > b)
    return -1;
  else if (a < b)
    return 1;
  return 0;
}

#endif
