#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */

//#define TEST_SPLIT 5

typedef enum inside 
{
  BEGIN, 
  IN, 
  OUT
} state;

int split(char* str, char* delimiters, char* split[])
{
  int ret = 0;
  int i = 0;
  int ch = *(str+i);
  state inside = BEGIN;
  int split_pos_start = 0;
  int split_pos_end = 0;  

  while( ch )
  {
    if( strchr( delimiters, ch ) == NULL ) 
    {
      switch( inside )
      {
        case BEGIN:
          ret++;
          inside = IN;
          split_pos_start = i;
          break;
        case IN:
          break;
        case OUT:
          ret++;
          inside = IN;
          split_pos_start = i;
          break;
      } 
    }
    else
    {
      switch( inside )
      {
        case BEGIN:
          break;
        case IN:
          inside = OUT;
          split_pos_end = i-1;
          split[ret-1] = (char *) malloc( 
              (split_pos_end - split_pos_start + 2) * sizeof(char) );
          strncpy( split[ret-1], str+split_pos_start,
              split_pos_end - split_pos_start + 1 ); 
          #ifdef TEST_SPLIT
          printf( "###%d:%s %d %d\n",
              ret, split[ret-1], split_pos_start, split_pos_end );
          #endif
          break;
        case OUT:
           split_pos_start = i;
           break;
      } 
    }
    i++;
    ch = *(str+i);
  }
  if( inside == IN )
  {
    split_pos_end = i-1;
    split[ret-1] = (char *) malloc( 
        (split_pos_end - split_pos_start + 2) * sizeof(char) );
    strncpy( split[ret-1], str+split_pos_start,
         split_pos_end - split_pos_start + 1 ); 
    #ifdef TEST_SPLIT
    printf( "###%d:%s %d %d\n",
       ret, split[ret-1], split_pos_start, split_pos_end );
    #endif
  }
  split[ret] = NULL;
  return ret;
}

int position( const char* elem, char* array[], int size )
{
  int i;

  for( i=0; i<size; i++ )
   if( strcmp(elem, array[i]) == 0 )
     return i;
  return -1; 
}

int main(void)
{
  char line[MAX_LINE*4];
  int argc;
  char *argv[MAX_LINE/2 + 1]; /* command line arguments */
  int background_execution;
  pid_t pid;
  int i;

  puts( "OSH Simple shell. Type 'exit' to exit...\n\n" );
  while( 1 ) 
  {
    printf("osh>");
    fflush(stdout);
    /* read and parse user input */
    gets( line );
    if( strcmp( line, "exit" ) == 0 )
    {
      puts( "Exiting...\n" );
      break;
    }
    argc = split(line, " \t\n", argv);
    #ifdef TEST_SPLIT
    for (i = 0; i<argc; i++)
      printf( "#%s# ", argv[i] );
    printf( "\n" );
    #endif
    background_execution = (position( "&", argv, argc ) >= 0)? 1:0;
    /* fork a child process */
    pid = fork();
    if (pid < 0) 
    { 
      /* error occurred */
      fprintf(stderr, "Fork Failed\n");
      break;
    }
    if (pid == 0) 
    { 
      /* child process */
      /* the child process will invoke execvp() */
      execvp(argv[0],argv);
    }
    else
    {
      /* parent process */
      /* if command included &, parent will not wait 
         for the child to complete */
      if( !background_execution )
        wait(NULL);
    }
    /* deallocation of parsed input*/
    for (i = 0; i<argc; i++)
      free( argv[i] );
  }
  return 0;
}


