all:
	g++ ./src/*.cpp main.cpp -lncurses -o game
	
run:
	./game