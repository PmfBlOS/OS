#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

/* Velicna bafera koji se koristi */
#define BUFF_SIZE 1024

/* Funkcija ispisuje primljenu poruku kao i string koji opisuje nastali problem.
   Potom prekida izvrsavanje programa. */
void error_fatal (char *message){
  perror (message);
  exit (1);
}

/* Program prepisuje ulaz na izlaz, koristeci read i write sistemske pozive */
int main()
{
  int read_chars = 1;
  char buffer[BUFF_SIZE];
  int write_chars;

  while ( read_chars > 0)
  {
    read_chars = read (STDIN_FILENO, buffer, sizeof (buffer));
    if( read_chars < 0 )
      error_fatal ("read error");    
    write_chars = write (STDOUT_FILENO, buffer, read_chars);
    if (write_chars != read_chars)
      error_fatal ("write error");
  } 
  return 0;
}
