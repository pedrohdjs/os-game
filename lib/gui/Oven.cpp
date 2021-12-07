#include "./Oven.hpp"

Oven::Oven(int id) 
: BorderedWindow(string("Forno " + to_string(id)), 10, 30, 2, 35*(id-1)+((WINDOW_WIDTH-35*4)/2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = OVEN_BUSY;

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
    this->drawInfo();
}

void Oven::drawInfo(){
    switch (status)
    {
    case OVEN_AVAILABLE:
        mvwprintw(window, 0, 7, "Forno disponivel");
        mvwprintw(window, 2, 7, "Aperte %d para assar", id);
        break;

    case OVEN_BUSY:
        mvwprintw(window, 0, 7, "Forno ocupado");
        mvwprintw(window, 4, 7, "Assando cookies...");

    case OVEN_NOT_PURCHASED:
        mvwprintw(window, 0, 7, "Forno indisponivel");
        mvwprintw(window, 2, 7, "Compre por 30 cookies", id);
        mvwprintw(window, 4, 7, "Aperte %d para comprar", id);
    default:
        break;
    }
}

void Oven::setStatus(int status){
    this->status = status;
}

void Oven::setProgress(float progress){
    this->progress = progress;
}