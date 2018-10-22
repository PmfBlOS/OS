PROGS	= cp
CC	= gcc
CFLAGS	= -Wall

progs : $(PROGS)

.PHONY : beauty clean

beauty :
	indent $(PROGS).c

clean :
	rm -f $(PROGS) *~