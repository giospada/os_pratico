#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int fd = inotify_init();
  int a = inotify_add_watch(fd, argv[1], IN_CREATE);

  size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1;
  struct inotify_event *event = malloc(bufsiz);
  do {
    DIR *d = opendir(argv[1]);
    struct dirent *t;
    while ((t = readdir(d)) != NULL) {
    }
    closedir(d);
    read(fd, event, bufsiz);

  } while (1);
  inotify_rm_watch(fd, a);
}
