#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "pid_manager.h"

#define LONG_BIT (sizeof(unsigned long)*CHAR_BIT)
#define RANGE_PID (MAX_PID-MIN_PID)
#define MAP_LONGS ((RANGE_PID / LONG_BIT ) + 1)

unsigned long *pid_map;

void bin(unsigned long n)
{
  unsigned long i;
  for (i = 1 << (LONG_BIT-1); i > 0; i = i / 2)
    (n & i)? printf("X"): printf("0");
  printf( " " );  
}

int allocate_map(void)
{
  pid_map = (unsigned long *) calloc(
                MAP_LONGS, sizeof(unsigned long));
  if( pid_map == NULL )
    return PID_ALLOCATION_FAIL;
  return PID_ALLOCATION_SUCESS;
}

int allocate_pid(void)
{
  int i,l,p;
  unsigned long x;
  unsigned int mask;
  for( i=0; i<RANGE_PID; i++ )
  {
    l = i / LONG_BIT;
    p = i - l * LONG_BIT;
    x = *( pid_map + l );
    mask = (1 << p);
    if( (x & mask) == 0 )
    {
      x = x ^ mask;
      *( pid_map + l ) = x;
      return (MIN_PID + i);
    }
  } 
  return PID_ALLOCATION_FAIL;
}

void release_pid(int pid)
{
  int l,p;
  unsigned long x;
  unsigned int mask;

  pid -= MIN_PID;
  l = pid / LONG_BIT;
  p = pid - l * LONG_BIT;
  x = *( pid_map + l );
  mask = (1 << p);
  if( (x & mask) != 0 )
  {
    x = x ^ mask;
    *( pid_map + l ) = x;
  } 
}

void print_map_allocation(void)
{
  int i;
  unsigned long x;

  #ifdef PROBLEM_EXISTS_MAP_ALLOCATION
  printf( "MAX_PID = %d \n", MAX_PID ); 
  printf( "MIN_PID = %d \n", MIN_PID ); 
  printf( "RANGE_PID = %d \n", RANGE_PID ); 
  printf( "LONG_BIT = %d \n", LONG_BIT ); 
  printf( "MAP_LONGS = %d \n", MAP_LONGS ); 
  #endif
  for( i=0; i<MAP_LONGS; i++ )
  {
    x = *(pid_map+i);
    bin( x );
  }
  printf( "\n" );
}


