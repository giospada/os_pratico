#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int explore(int nested, const char *path) {
  DIR *temp = opendir(path);
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

    char *buffer = malloc(strlen(path) + strlen(currnet->d_name) + 2);
    sprintf(buffer, "%s/%s", path, currnet->d_name);
    explore(nested + 1, buffer);
    free(buffer);
  }
  closedir(temp);
  return 0;
}

int main(int argc, char *argv[]) { explore(0, "/tmp"); }
