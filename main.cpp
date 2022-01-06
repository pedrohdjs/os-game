#include "./lib/game.hpp"
#include <csignal>

Game* newGame;

void killGame(int) {
    delete newGame;
    exit(0);
}

void resize(int) {
    newGame->resize();
}

int main(int argc, char** argv) {
    newGame = new Game();

	std::signal(SIGWINCH, resize);
    std::signal(SIGINT, killGame);
    std::signal(SIGTERM, killGame);
    std::signal(SIGHUP, killGame);

    newGame->run();
    delete newGame;
	
    return 0;
}