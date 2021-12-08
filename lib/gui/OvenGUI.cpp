#include "./OvenGUI.hpp"

OvenGUI::OvenGUI(int id) 
: BorderedWindow(string("Forno " + to_string(id)), 15, 30, 2, 35*(id-1)+((WINDOW_WIDTH-35*4)/2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = OVEN_BUSY;
    this->progress = 1;

    this->setup();
}

void OvenGUI::setup(){
    BorderedWindow::setup();

    //Desenha o esqueleto do forno
    mvwprintw(window, 8, 2, "/ \\");
    mvwprintw(window, 9, 2, "| |");
    mvwprintw(window, 10, 0, "|-----|");
    mvwprintw(window, 11, 0, "|     |");
    mvwprintw(window, 12, 0, "|-----| [");
    mvwprintw(window, 12, width-1, "]");
}

void OvenGUI::refresh(){
    BorderedWindow::refresh();
}

void OvenGUI::draw(){
    this->drawInfo();
    if (this->status == OVEN_BUSY){
        this->drawProgressBar();
        this->drawSmoke();
    }
}

void OvenGUI::drawInfo(){
    switch (status)
    {
    case OVEN_AVAILABLE:
        mvwprintw(window, 0, 0, "Forno disponivel");
        mvwprintw(window, 2, 0, "Aperte %d para assar", id);
        break;

    case OVEN_BUSY:
        mvwprintw(window, 0, 0, "Forno ocupado");
        mvwprintw(window, 4, 0, "Assando cookies...");
        mvwprintw(window, 11, 3, "O");
        break;

    case OVEN_NOT_PURCHASED:
        mvwprintw(window, 0, 0, "Forno indisponivel");
        mvwprintw(window, 2, 0, "Compre por 30 cookies", id);
        mvwprintw(window, 4, 0, "Aperte %d para comprar", id);
        mvwprintw(window, 11, 3, "X");
        break;
    
    default:
        break;
    }
}

void OvenGUI::drawProgressBar(){
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * progress);
    wmove(window, 12, 9);
    for(int i = 0; i < maxWidth; i++){
        if (i < progressWidth){
            waddch(window, '=');
        } else {
            waddch(window, ' ');
        }
    }
}

void OvenGUI::drawSmoke(){
    if (progress == 0) return;
    int smokeState = (int)6*progress;
    if(smokeState >= 1 && smokeState <= 3) mvwprintw(window, 7, 3, "O");
    if(smokeState >= 2 && smokeState <= 4) mvwprintw(window, 6, 4, "O");
    if(smokeState >= 3 && smokeState <= 5) mvwprintw(window, 5, 3, "O");
}

void OvenGUI::setStatus(int status){
    this->status = status;
}

void OvenGUI::setProgress(float progress){
    this->progress = progress;
}