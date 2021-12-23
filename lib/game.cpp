#include "./game.hpp"

Game::Game() : gui{7, 100} {
    //target = 100;
}

void Game::run() {
    GameStats::start();
    gui.show();
}
