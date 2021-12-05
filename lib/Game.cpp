#include "./Game.hpp"

Game::Game(){
    this->target = 2500;
    this->gui = new GameGUI(2,100);
}

void Game::run(){
    gui->show();
    getch();
    delete gui;
}
