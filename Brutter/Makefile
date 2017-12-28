CC=gcc
#CFLAGS=-I. -DPRINT_ITERATION_OUTPUT
CFLAGS=-I.
LIBS=-lm
OBJ = main.o bruteforce.o crypter.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

brutter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
