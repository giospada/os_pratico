#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo, siginfo_t *info, void *context) {
  char *s = (char *)&info->si_value.sival_int;
  char s2[5];
  for (int i = 0; i < 4; i++) {
    s2[i] = s[i];
  }
  s2[4] = '\0';
  printf("%s", s2);
  fflush(stdout);
  sigqueue(info->si_pid, SIGUSR1, (union sigval)0);
}

int main(int argc, char *argv[]) {
  printf("%d\n", getpid());
  struct sigaction act = {0};

  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = &handler;

  if (sigaction(SIGUSR1, &act, NULL) == -1) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }
  while (1)
    pause();

  return 0;
}
