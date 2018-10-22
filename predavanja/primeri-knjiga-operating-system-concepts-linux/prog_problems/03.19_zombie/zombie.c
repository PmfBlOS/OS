#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid;
  /* fork a child process */
  pid = fork();
  if (pid < 0) 
  { 
    /* error occurred */
    fprintf(stderr, "Fork Failed\n");
    return 1;
  }
  if (pid == 0) 
  { 
    /* this is a child: dies immediately and becomes zombie */
    exit(0); 
  }
  else 
  { 
    /* parent process: just asks for the user input */
    printf("Press enter after looking at the zombie process...");
    (void)getchar(); 
  }
  return 0;
}



