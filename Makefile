all:
	g++ ./lib/*.cpp main.cpp \
	./lib/gui/*.cpp \
	-lncurses -pthread -o game
	
run:
	./game