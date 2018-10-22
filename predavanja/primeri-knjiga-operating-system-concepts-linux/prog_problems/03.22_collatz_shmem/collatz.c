#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* the size (in bytes) of shared memory object */
# define SHM_SIZE 4096


int collatz_next(int n)
{
  if( n % 2 )
    return (3*n+1);
  return (n/2);
}

int main(int argc, char *argv[])
{
  /* starting value for collatz array */
  int n;
  /* name of the shared memory object */
  const char *name = "COLLATZ";
  /* shared memory file descriptor */
  int shm_fd;
  /* pointer to shared memory obect */
  void *ptr;
  /* child process identifikator */
  pid_t pid;
  /* for output */
  char temp[SHM_SIZE];  

  /* obtain collatz starting value from command line */
  if( argc != 2 )
  {
    fprintf(stderr, "Usage: collatz <n>");
    return 1;    
  }
  n = atoi( argv[1] );
  /* create the shared memory object */
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  /* configure the size of the shared memory object */
  ftruncate(shm_fd, SHM_SIZE);
  /* memory map the shared memory object */
  ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

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
      sprintf( temp, "%d ", n );
      sprintf(ptr, "%s", temp );
      ptr += strlen( temp );
      n = collatz_next( n );
    } while( n != 1 );
    strcpy( temp, "1 \n" );
    sprintf( ptr, "%s", temp );
    ptr += strlen( temp );
  }
  else 
  { 
    /* parent process */
    wait(NULL);
    printf("Child process terminated\n");
    /* open the shared memory object */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    /* memory map the shared memory object */
    ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    /* read from the shared memory object and print to output */
    printf("%s",(char *)ptr);
    /* remove the shared memory object */
    shm_unlink(name);
  }
  return 0;
}


