#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 25

int main(VOID)
{
	HANDLE ReadHandle;
	CHAR buffer[BUFFER_SIZE];
	DWORD read;

	printf("Child...\n");
	/* get the read handle of the pipe */
	ReadHandle = GetStdHandle(STD_INPUT_HANDLE);
	/* the child reads from the pipe */
	if (ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL))
		printf("child read %s\n",buffer);
	else
		fprintf(stderr, "Error reading from pipe");
	printf("Child finished.\n");	
	return 0;
}