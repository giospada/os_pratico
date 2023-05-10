
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int explore(int nested, const char *path, int fd) {
  int fd_new = openat(fd, path, O_RDONLY);
  DIR *temp = fdopendir(fd_new);
  if (temp == NULL)
    return -1;
  struct dirent *currnet;
  while ((currnet = readdir(temp)) != NULL) {
    if (currnet->d_name[0] == '.') {
      continue;
    }

    for (int i = 0; i < nested; i++)
      printf("\t");
    printf("%s\n", (*currnet).d_name);
    fflush(stdout);

    explore(nested + 1, currnet->d_name, fd_new);
  }
  closedir(temp);
  return 0;
}

int main(int argc, char *argv[]) { explore(0, "/tmp", open(".", O_RDONLY)); }
