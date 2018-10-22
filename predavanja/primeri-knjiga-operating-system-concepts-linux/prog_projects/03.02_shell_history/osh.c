#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */
#define HISTORY_LEN 10 /* length of the history */

//#define TEST_SPLIT 
//#define TEST_HISTORY 

typedef enum inside 
{
  BEGIN, 
  IN, 
  OUT
} state;

int insert( char* str, char** array, int size, int limit )
{
  int i;
  
  #ifdef TEST_HISTORY
  printf( "#HISTORY# str=%s\n", str );
  printf( "#HISTORY# size=%d limit=%d\n", size, limit );
  #endif
  if( size < limit )
    size ++;
  for( i=size-1; i>0; i-- )
    array[i] = array[i-1];
  array[0] = (char *) malloc( (strlen(str) + 1) * sizeof(char) );
  strcpy( array[0], str );
  return size;
}

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
          printf( "#SPLIT#%d:%s %d %d\n",
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
    printf( "#SPLIT#%d:%s %d %d\n",
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
  char* history[HISTORY_LEN];
  int history_size;
  int argc;
  char *argv[MAX_LINE/2 + 1]; /* command line arguments */
  int background_execution;
  pid_t pid;
  int i;
  int n = -1;

  history_size = 0;
  printf( "==========================================\n" );
  printf( "OSH Simple shell. Type 'Ctrl+C' to exit...\n" );
  printf( "==========================================\n" );
  while( 1 ) 
  {
    printf("osh>");
    fflush(stdout);
    /* read and parse user input */
    gets( line );
    if( strcmp( line, "exit" ) == 0 )
    {
      puts( "Exiting OSH Simple shell...\n" );
      /* deallocation of the history */
      for( i=0; i<history_size; i++ )
        free( history[i] );
      exit(0);
    }
    else
    {
      /* obtain command and its arguments */
      argc = split(line, " \t\n", argv);
      #ifdef TEST_SPLIT
      for (i = 0; i<argc; i++)
        printf( "#SPLIT#%s# ", argv[i] );
      printf( "#SPLIT#\n" );
      #endif
      if( strcmp( line, "history" ) == 0 )
      {
        if( history_size > 0 )
        {
          for( i=history_size-1; i>=0; i-- )
            printf( "%3d %s\n", (i+1), history[i] );
        }
        else
          printf("No history.\n");
        continue;
      }
      else if( strcmp(argv[0], "!!") == 0 )
      {
        if( history_size > 0 )
        {
          strcpy( line, history[0] ); 
          argc = split(line, " \t\n", argv);
        }
        else
        {
          printf("No commands in history.\n");
          continue;
        }
      }
      else if( strcmp(argv[0], "!") == 0 )
      {
        if( argc > 1 )
          n = atoi( argv[1] );
        if( (n>0) && (history_size >= n)  )
        {
          strcpy( line, history[n-1] ); 
          n = -1;
          argc = split(line, " \t\n", argv);
        }
        else
        {
          printf("No such command in history.\n");
          continue;
        }
      }
      /* insert into history non-history commands */
      history_size = insert( line, history, history_size, HISTORY_LEN);
      /* check if it is background execution */
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
  }
  /* deallocation of the history */
  for( i=0; i<history_size; i++ )
    free( history[i] );
  return 0;
}


