compile: src/Program.c
	gcc src/Program.c -o bin/music -lraylib

run: bin/music
	gcc src/Program.c -o bin/music -lraylib
	./bin/music ./bin/*.mp3

install: bin/music 
	sudo cp bin/music /bin/fmp
