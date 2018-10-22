CC = gcc # Compiler to use
OPTIONS = -O2 -g -Wall -lrt # -g for debug, -O2 for optimise and -Wall additional messages -lrt for POSIX shared libraries
INCLUDES = -I . # Directory for header file
OBJS = collatz.o # List of objects to be build
.PHONY: all clean # To declare all, clean are not files
 
all: ${OBJS}
	@echo "Building.." # To print "Building.." message
	${CC} ${OPTIONS} ${INCLUDES} ${OBJS} -o collatz
 
%.o: %.c  # % pattern wildcard matching
	${CC} ${OPTIONS} -c $*.c ${INCLUDES}
list:
	@echo $(shell ls) # To print output of command 'ls'
 
clean:
	@echo "Cleaning up.."
	-rm -rf *.o # - prefix for ignoring errors and continue execution
	-rm target_bin
