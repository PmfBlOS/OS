#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int collatz_next(int n)
{
  if( n % 2 )
    return (3*n+1);
  return (n/2);
}

int main(int argc, char *argv[])
{
  int n;
  pid_t pid;
  if( argc != 2 )
  {
    fprintf(stderr, "Usage: collatz <n>");
    return 1;    
  }
  n = atoi( argv[1] );
  pid = fork();
  if (pid < 0) 
  { 
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 2;
  }  
  if (pid == 0) 
  { 
    /* child process */
    do
    {
      printf("%d ",n);
      n = collatz_next( n );
    } while( n != 1 );
    printf( "1 \n" );
  }
  else 
  { 
    /* parent process */
    wait(NULL);
    printf("Child Complete\n");
  }
  return 0;
}


