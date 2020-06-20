CC=cc
CXX=CC
# CCFLAGS= -g -Wall -Werror
CCFLAGS= -g -std=c99 -Wall -Werror

all: main test

# Compile all .c files in .o files
%.o : %.c
	$(CC) -c $(CCFLAGS) $<

# Link object files
main: main.o mymath.o
	$(CC) -o main main.o mymath.o

test: main
	./main

clean: 
	rm -rf *.o main
