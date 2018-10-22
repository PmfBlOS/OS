#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MSG_SIZE 50

int main(int argc, char** argv)
{
  /* the size (in bytes) of shared memory object */
  const int SIZE =4096;
  /* name of the shared memory object */
  const char *name = "OS";
  /* strings written to shared memory */
  char message_0[MSG_SIZE] = "Hello ";
  char message_1[MSG_SIZE] = "World";
  /* shared memory file descriptor */
  int shm_fd;
  /* pointer to shared memory obect */
  void *ptr;
  if( argc == 0 )
  {
    strncpy( message_0, "Zdravo ", MSG_SIZE); 
    strncpy( message_1, "Svete", MSG_SIZE); 
  }
  else if( argc == 1 )
  {
    strncpy( message_0, argv[1], MSG_SIZE);
    strncpy( message_1, "\n", MSG_SIZE);     
  }
  else
  {
    strncpy( message_0, argv[1], MSG_SIZE);
    strncpy( message_1, argv[2], MSG_SIZE);
  }
  /* create the shared memory object */
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  /* configure the size of the shared memory object */
  ftruncate(shm_fd, SIZE);
  /* memory map the shared memory object */
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  /* write to the shared memory object */
  sprintf(ptr,"%s",message_0);
  ptr += strlen(message_0);
  sprintf(ptr,"%s",message_1);
  ptr += strlen(message_1);
  return 0;
}


