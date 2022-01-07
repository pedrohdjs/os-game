#include "./game.hpp"

Game::Game() {
    gui = new GameGUI(7);
}

void Game::run() {
    GameStats::start();  //define o status do jogo como inicializado

    gui->detectMinimumTerminalSize();

    gui->startGameScreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    start();
    gui->show();

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    finish();

    gui->endGameScreen();
}

void Game::start() {
    Customers::start();

    for (auto& cook : GameStats::Cooks) {
        cook->start();
    }

    for (auto& oven : GameStats::Ovens) {
        oven->start();
    }
}

void Game::finish() {
    //fica em loop enquanto espera o encerramento de todas as threads
    while (GameStats::getNumberOfThreads() > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    flushinp();
}

Game::~Game() {
    GameStats::end();
    finish();

    for (int i = 0; i < 4; i++) {
        delete GameStats::Ovens[i];
        delete GameStats::Cooks[i];
    }

    delete gui;
}
