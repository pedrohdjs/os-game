all:
	g++ ./lib/*.cpp main.cpp -lncurses -o game
	
run:
	./game