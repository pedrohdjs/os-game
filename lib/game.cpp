#include "./game.hpp"

Game::Game() {
    gui = new GameGUI(7);
}

void Game::run() {
    GameStats::start();
    gui->show();
}

void Game::resize() {
    //gui->show();
}

Game::~Game() {
    GameStats::end();
    while (GameStats::getNumberOfThreads() > 0)
        ;
    delete gui;
}
