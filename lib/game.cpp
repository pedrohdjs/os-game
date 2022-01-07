#include "./game.hpp"

Game::Game() {
    gui = new GameGUI(7);
}

void Game::run() {
    GameStats::start();
    Customers::start();
    gui->show();
    finish();
}

void Game::resize() {
    clear();
    gui->refresh();
    gui->setup();
    endwin();
    refresh();
}

void Game::finish() {
    while (GameStats::getNumberOfThreads() > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

Game::~Game() {
    GameStats::end();
    finish();
    delete gui;
}
