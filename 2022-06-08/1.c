#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *allocStr(int len) { return malloc(len * sizeof(char)); }

int isAbsPath(char *path) { return path[0] == '/'; }

char *copystring(char *path) {
  char *copied = allocStr(strlen(path) + 1);
  strcpy(copied, path);
  return copied;
}

char *appendIfNotAbsPath(char *path, char *currentPath) {
  if (isAbsPath(path)) {
    return realpath(path, NULL);
  }
  int len = strlen(path) + strlen(currentPath) + 2;
  char concatPath[len];
  char *newstr = allocStr(len);
  sprintf(concatPath, "%s/%s", currentPath, path);
  return realpath(concatPath, NULL);
}

int invertlink(char *syslinkPath) {
  char pointedPath[PATH_MAX];
  if (readlink(syslinkPath, pointedPath, PATH_MAX) == -1) {
    printf("not link file \n");
    exit(1);
  }
  char *pathCopy = copystring(syslinkPath);
  char *endPath = appendIfNotAbsPath(pointedPath, dirname(pathCopy));
  printf("%s  ->  %s -> %s \n", syslinkPath, pointedPath, endPath);
  unlink(syslinkPath);
  link(endPath, syslinkPath);
  unlink(endPath);
  symlink(syslinkPath, endPath);
  free(pathCopy);
  free(endPath);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("%s [filename] \n", argv[0]);
    return 1;
  }
  invertlink(argv[1]);
  return 0;
}
