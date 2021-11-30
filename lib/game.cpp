#include "./game.hpp"

Game::Game(){
    this->msg = "Hello, jogo de SO!";
}

void Game::run(){
    cout << this->msg << endl;
}
