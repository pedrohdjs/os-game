#include "./Oven.hpp"

Oven::Oven(int id) 
: BorderedWindow(string("Forno " + to_string(id)), 10, 30, 2, 35*(id-1)+((WINDOW_WIDTH-35*4)/2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = OVEN_NOT_PURCHASED;

    this->setup();
}

void Oven::setup(){
    BorderedWindow::setup();

    //Desenha o esqueleto do forno
    mvwprintw(window, 3, 2, "/ \\");
    mvwprintw(window, 4, 2, "| |");
    mvwprintw(window, 5, 0, "|-----|");
    mvwprintw(window, 6, 0, "|     |");
    mvwprintw(window, 7, 0, "|-----|");
}

void Oven::refresh(){
    BorderedWindow::refresh();
}

void Oven::draw(){

}


void Oven::setStatus(int status){
    this->status = status;
}

void Oven::setProgress(float progress){
    this->progress = progress;
}