
# compilers, linkers, utilities, and flags
CC = gcc
CFLAGS = -Wall -g
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(CFLAGS) -o $@ 

# implicit rule to build .o from .c files
%.o: %.c 
	$(COMPILE) -c -o $@ $<


# explicit rules
all: timeout snooze

timeout: main.o
	$(LINK) main.o

snooze: tests/snooze.o
	$(LINK) tests/snooze.o

clean:
	rm -f *.o snooze timeout
