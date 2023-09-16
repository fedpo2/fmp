CC = gcc
CFLAGS = -o ./fmp -lraylib -O3

compile: ./src/Program.c ./src/linkedList.c
	$(CC) $(CFLAGS) ./src/Program.c ./src/linkedList.c

install: ./src/Program.c
	$(CC) $(CFLAGS) ./src/Program.c 
	sudo cp ./fmp /bin/fmp
