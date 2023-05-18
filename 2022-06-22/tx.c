#include <dirent.h>
#include <libgen.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pid_t pid;

int lock = 1;

void handler(int signo, siginfo_t *info, void *context) {
  // arrived signal
  lock = 0;
}

void sendString(char *c) {
  for (int i = 0; i < strlen(c); i += 4) {
    union sigval temp;
    temp.sival_int = *((int *)(c + i));
    sigqueue(pid, SIGUSR1, temp);
    if (lock)
      pause();
    lock = 1;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    perror("non i parametri giusti");
  }
  pid = atoi(argv[1]);
  if (kill(pid, 0) == -1) {
    perror("non raggiungibile");
  }

  struct sigaction act = {0};

  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = &handler;

  if (sigaction(SIGUSR1, &act, NULL) == -1) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  sendString(argv[2]);

  return 0;
}
