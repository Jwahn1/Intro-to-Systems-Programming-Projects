# compilers, linkers, utilities, and flags
CC = gcc
CFLAGS = -Wall -O3 -fno-builtin

COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(CFLAGS) -o $@ 

# implicit rule to build .o from .c files
%.o: %.c 
	$(COMPILE) -c -o $@ $<


# explicit rules
faststr: main.o strlen.o ticks.o
	$(LINK) main.o strlen.o ticks.o

clean:
	rm -f *.o faststr
