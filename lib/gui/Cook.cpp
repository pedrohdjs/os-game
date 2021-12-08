#include "./Cook.hpp"

Cook::Cook(int id) 
: BorderedWindow(string("Funcionario " + to_string(id)), 11, 30, 18, 35*(id-1)+((WINDOW_WIDTH-35*4)/2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = (id == 1) ? COOK_AVAILABLE : COOK_NOT_PURCHASED;
    this->skill = 1;

    this->setup();
}

void Cook::setup(){
    BorderedWindow::setup();

    //Desenha o funcionario
    mvwprintw(window, 6, 1, "O");
    mvwprintw(window, 7, 0, "/|\\");
    mvwprintw(window, 8, 0, "/ \\");
}

void Cook::refresh(){
    BorderedWindow::refresh();
}

void Cook::draw(){
    this->drawInfo();
}

void Cook::drawInfo(){
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};
    
    switch (status)
    {
    case COOK_AVAILABLE:
        mvwprintw(window, 0, 0, "Funcionario disponivel");
        mvwprintw(window, 2, 0, "Faz %d cookies por fornada", skill);
        mvwprintw(window, 4, 0, "Aperte %c para evoluir", actionKeys[id-1]);
        break;

    case COOK_BUSY:
        mvwprintw(window, 0, 0, "Funcionario ocupado");
        mvwprintw(window, 2, 0, "Faz %d cookies por fornada", skill);
        mvwprintw(window, 4, 0, "Aperte %c para evoluir", actionKeys[id-1]);

    case COOK_NOT_PURCHASED:
        mvwprintw(window, 0, 0, "Funcionario nao contratado");
        mvwprintw(window, 4, 0, "Aperte %c para comprar", actionKeys[id-1]);
    default:
        break;
    }

}

void Cook::setStatus(int status){
    this->status = status;
}

void Cook::setSkill(int skill){
    this->skill = skill;
}