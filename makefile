compile: src/Program.cpp
	g++ src/Program.cpp -o bin/music -lraylib 

run: bin/music
	g++ src/Program.cpp -o bin/music -lraylib
	./bin/music ./bin/*.mp3

install: bin/music 
	sudo cp bin/music /bin/fmp
