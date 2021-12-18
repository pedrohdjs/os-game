#include "./Game.hpp"

Game::Game(){
    this->target = 100;
    this->gui = new GameGUI(7,target);
}

void Game::run(){
    GameStats::start();
    gui->show();
    delete gui;
}
