#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("%s [filename] \n", argv[0]);
    return 1;
  }

  char name[PATH_MAX + 1];

  readlink(argv[1], name, PATH_MAX);
  char buff[PATH_MAX + 1];
  char *base = malloc(sizeof(char) * (strlen(argv[1]) + 1));
  strcpy(base, argv[1]);
  base = dirname(base);
  char *allsyspath = malloc((strlen(base) + strlen(name) + 2) * sizeof(char));
  sprintf(allsyspath, "%s/%s", base, name);
  char *rpath = realpath(allsyspath, buff);
  printf("%s\n", buff);
  if (rpath == NULL) {
    return -1;
  }
  unlink(argv[1]);
  link(buff, argv[1]);
  unlink(buff);
  symlink(argv[1], buff);
  free(allsyspath);
  return 0;
}
