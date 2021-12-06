#include "./Game.hpp"

Game::Game(){
    this->target = 100;
    this->gui = new GameGUI(2,target);
}

void Game::run(){
    gui->show();
    delete gui;
}
