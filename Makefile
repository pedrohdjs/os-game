all:
	g++ ./lib/*.cpp ./lib/gui/*.cpp ./lib/cooker/*.cpp ./lib/utils/*.cpp ./lib/oven/*.cpp \
	main.cpp \
	-lncurses -pthread -o game
	
run:
	./game