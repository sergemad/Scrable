OPTIONS=-g -Wall -std=c++11

all: bin/main

bin/bonus.o: src/bonus.cpp src/bonus.hpp
	g++ $(OPTIONS) -o bin/bonus.o -c src/bonus.cpp
	
bin/spot.o: src/spot.cpp src/spot.hpp src/bonus.hpp
	g++ $(OPTIONS) -o bin/spot.o -c src/spot.cpp

bin/board.o: src/board.cpp src/board.hpp src/spot.hpp
	g++ $(OPTIONS) -o bin/board.o -c src/board.cpp

bin/saclettre.o: src/saclettre.cpp src/saclettre.hpp
	g++ $(OPTIONS) -o bin/saclettre.o -c src/saclettre.cpp

bin/Arbre_G.o: src/Arbre_G.cpp src/Arbre_G.hpp
	g++ $(OPTIONS) -o bin/Arbre_G.o -c src/Arbre_G.cpp
	
bin/Partie.o: src/Partie.cpp src/Partie.hpp src/Arbre_G.hpp src/saclettre.hpp src/board.hpp
	g++ $(OPTIONS) -o bin/Partie.o -c src/Partie.cpp

bin/testlettre.o: src/testlettre.cpp src/Partie.hpp
	g++ $(OPTIONS) -o bin/testlettre.o -c src/testlettre.cpp

bin/main: bin/testlettre.o bin/Partie.o bin/Arbre_G.o bin/saclettre.o bin/board.o bin/spot.o bin/bonus.o
	g++ $(OPTIONS) -o bin/main bin/testlettre.o bin/Partie.o bin/Arbre_G.o bin/saclettre.o bin/board.o bin/spot.o bin/bonus.o

clean:
	rm -f *.o bin/main
