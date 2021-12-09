#include "./Game.hpp"

Game::Game(){
    this->target = 100;
    this->gui = new GameGUI(7,target);
}

void Game::run(){
    //Usar os getters da gui
    //gui->getOvens()[0];
    gui->show();
    delete gui;
}
