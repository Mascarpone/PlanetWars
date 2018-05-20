################################################################
# Makefile variables
################################################################

# Compilation flags
CC=gcc
CFLAGS=-std=c99
LDFLAGS=-lm

# List of source files
SRC= $(wildcard *.c)

#List of object files
OBJ= $(SRC:.c=.o)


################################################################
# Makefile rules
################################################################

passivebot: passivebot.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

randbot: randbot.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

IAtapette: IAtapette.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

chaine: chaine.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)
	mv chaine ../test/client/bin/


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o
