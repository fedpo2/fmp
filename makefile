compile: src/Program.cpp
	g++ src/Program.cpp -o bin/music -lraylib 

run: src/Program.cpp
	g++ src/Program.cpp -o bin/music -lraylib & ./bin/music ~/Music/Metallica/*
