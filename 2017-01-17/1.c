#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

int size = 10;
int current_size = 0;
ino_t *arr;

void init() { ino_t *arr = malloc(sizeof(ino_t) * size); }

void alloc() {
  size *= 2;
  ino_t *c = malloc(sizeof(ino_t) * size);
  for (int i = 0; i < current_size; i++) {
    c[i] = arr[i];
  }
  ino_t *t = arr;
  arr = c;
  free(t);
}
int isInside(ino_t current) {
  for (int i = 0; i < current_size; i++) {
    if (arr[i] == current) {
      return 1;
    }
  }
  return 0;
}

void recursiveSearch(const char *path) {
  DIR *c = opendir(path);
  struct dirent *direntry;
  while ((direntry = readdir(c)) != NULL) {
    if (direntry->d_type == DT_REG || direntry->d_ino == DT_DIR) {
      ino_t prova = direntry->d_ino;
      if (!isInside(prova)) {
        arr[current_size] = prova;
        current_size++;
        if (current_size == size)
          alloc();
        if (direntry->d_ino == DT_DIR) {
          char path[MAX_PATH];
          sprintf(path, "%s/%s", path, direntry->d_name);
          recursiveSearch(path);
        }
      }
    }
  }
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    printf("args error");
    return -1;
  }
  recursiveSearch(argv[1]);
  printf("%d", current_size);
}
