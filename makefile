CC = gcc
CFLAGS = -o ./fmp -lraylib

compile: ./src/Program.c
	$(CC) $(CFLAGS) ./src/Program.c

install: ./src/Program.c
	$(CC) $(CFLAGS) ./src/Program.c 
	sudo cp ./fmp /bin/fmp
