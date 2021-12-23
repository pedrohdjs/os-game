#include "./game.hpp"

Game::Game() : gui{7, 100} {
    //target = 100;
}

bool Game::run() {
    GameStats::start();
    gui.show();

    return GameStats::victory;
}
