#include "./CookGUI.hpp"

CookGUI::CookGUI(int id) 
: BorderedWindow(string("Funcionario " + to_string(id)), 11, 30, 18, 35*(id-1)+((WINDOW_WIDTH-35*4)/2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = (id == 1) ? COOK_AVAILABLE : COOK_NOT_PURCHASED;
    this->skill = 1;

    this->setup();
}

void CookGUI::setup(){
    BorderedWindow::setup();

    //Desenha o funcionario
    mvwprintw(window, 6, 1, "O");
    mvwprintw(window, 7, 0, "/|\\");
    mvwprintw(window, 8, 0, "/ \\     [");
    mvwprintw(window, 8, width-1, "]s");
}

void CookGUI::refresh(){
    BorderedWindow::refresh();
}

void CookGUI::drawProgressBar() {
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * progress);
    wmove(window, 8, 9);
    for (int i = 0; i < maxWidth; i++) {
        if (i < progressWidth) {
            waddch(window, '=');
        } else {
            waddch(window, ' ');
        }
    }
}

void CookGUI::draw(){

    drawInfo();
    drawProgressBar();
}

void CookGUI::drawInfo(){
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

void CookGUI::setStatus(int status){
    this->status = status;
}

void CookGUI::setSkill(int skill){
    this->skill = skill;
}

void CookGUI::setProgress(float progress) {
    this->progress = progress;
}