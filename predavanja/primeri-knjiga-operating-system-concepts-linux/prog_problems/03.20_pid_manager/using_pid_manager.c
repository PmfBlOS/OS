#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include "pid_manager.h"

int main()
{
  int status;
  int i;
  int pid1, pid2, pid3;

  printf( "\n Allocating map \n");
  status = allocate_map();
  if( status != PID_ALLOCATION_SUCESS )
  { 
    /* error occurred */
    fprintf(stderr, "Error in map allocation");
    return PID_ALLOCATION_FAIL;
  }
  printf( "\n Map at begining \n");
  print_map_allocation();
  printf( "\n Allocating process ids \n");
  pid1 = allocate_pid();
  if( pid1 == PID_ALLOCATION_FAIL )
  {
    /* error occurred */
    fprintf(stderr, "Error in process id allocation");
    return PID_ALLOCATION_FAIL;
  }
  printf( "Allocated pid %d \n", pid1 );
  
  pid2 = allocate_pid();
  if( pid2 == PID_ALLOCATION_FAIL )
  {
    /* error occurred */
    fprintf(stderr, "Error in process id allocation");
    return PID_ALLOCATION_FAIL;
  }
  printf( "Allocated pid %d \n", pid2 );

  pid3 = allocate_pid();
  if( pid3 == PID_ALLOCATION_FAIL )
  {
    /* error occurred */
    fprintf(stderr, "Error in process id allocation");
    return PID_ALLOCATION_FAIL;
  }
  printf( "Allocated pid %d \n", pid3 );

  printf( "\n Map after allocation \n");
  print_map_allocation();

  release_pid( pid2 );
  printf( "\n Map after release 2 \n");
  print_map_allocation();

  release_pid( pid1 );
  printf( "\n Map after release 1 \n");
  print_map_allocation();

  release_pid( pid3 );
  printf( "\n Map after release 3 \n");
  print_map_allocation();

  return 0;
}


