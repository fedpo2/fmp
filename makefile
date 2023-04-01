compile: src/Program.cpp
	g++ src/Program.cpp -o bin/music -lraylib 

run: bin/music 
	./bin/music ./bin/*.mp3
