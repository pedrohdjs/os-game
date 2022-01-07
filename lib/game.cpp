#include "./game.hpp"

Game::Game() {
    gui = new GameGUI(7);
}

void Game::run() {
    GameStats::start();
    gui->show();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    finish();
    gui->endGameScreen();
    timeout(-1);
    getch();
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
    flushinp();
}

Game::~Game() {
    GameStats::end();
    finish();
    delete gui;
}
