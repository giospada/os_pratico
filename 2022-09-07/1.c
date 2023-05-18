#include <stdio.h>
#include <sys/wait.h>
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
      waitpid(forkvalue, &status, 0);
      success = WEXITSTATUS(status) == 0;
    }
  } while (success);
}
