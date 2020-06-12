#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
  pid_t pid1, pid2, pid3;
  if ((pid1= fork()) == 0) {
    execlp("./exe", NULL, NULL, NULL); 
  }
  int status;
  waitpid(pid1, &status, 0);

  
  
}
 
