#include "./Game.hpp"

Game::Game(){
    this->target = 2500;
    this->gui = new GameGUI(10);
}

void Game::run(){
    gui->show();
    getch();
    delete gui;
}
