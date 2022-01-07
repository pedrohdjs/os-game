all:
	g++ ./lib/*.cpp ./lib/gui/*.cpp ./lib/cooker/*.cpp ./lib/game-stats/*.cpp ./lib/oven/*.cpp ./lib/customers/*.cpp \
	main.cpp \
	-lncurses -pthread -o game
	
run:
	./game