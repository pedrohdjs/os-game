all:
	g++ ./lib/*.cpp main.cpp \
	./lib/gui/*.cpp \
	./lib/gui/box-window/*.cpp \
	./lib/gui/main/*.cpp \
	-lncurses -pthread -o game
	
run:
	./game