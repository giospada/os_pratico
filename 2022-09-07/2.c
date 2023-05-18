#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int success = 0;
  do {
    pid_t forkvalue = fork();
    if (forkvalue < 0) {
      perror("");
    } else if (forkvalue == 0) {
      execvp(argv[1], argv + 1);
    } else {
      int status;
      struct timeval t;
      gettimeofday(&t, NULL);
      waitpid(forkvalue, &status, 0);
      success = WEXITSTATUS(status) == 0;
      if (!success)
        break;
      struct timeval t2;
      gettimeofday(&t2, NULL);
      time_t c = t2.tv_sec - t.tv_sec + (t2.tv_usec < t.tv_usec ? -1 : 0);
      success = c > 0;
    }
  } while (success);
}
