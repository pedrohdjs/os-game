#include "./CookGUI.hpp"

CookGUI::CookGUI(int id)
    : BorderedWindow(string("Funcionario " + to_string(id)), 11, 30, 18, 35 * (id - 1) + ((GameStats::WINDOW_WIDTH - 35 * 4) / 2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = (id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED;
    this->skill = 1;

    this->setup();
}

void CookGUI::setup() {
    BorderedWindow::setup();

    //Desenha o funcionario
    mvwprintw(window, 6, 1, "O");
    mvwprintw(window, 7, 0, "/|\\");
    mvwprintw(window, 8, 0, "/ \\     [");
    mvwprintw(window, 8, width - 1, "]s");
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

void CookGUI::draw() {
    drawInfo();
    drawProgressBar();
}

void CookGUI::onRefresh() {
    progress += (progress > 1.0) ? -progress: 0.05;
}

void CookGUI::drawInfo() {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};

    switch (status) {
        case GameStats::AVAILABLE:
            mvwprintw(window, 0, 0, "Funcionario disponivel    ");
            mvwprintw(window, 2, 0, "Faz %d cookies por fornada", skill);
            mvwprintw(window, 4, 0, "Aperte %c para evoluir", actionKeys[id - 1]);
            break;

        case GameStats::BUSY:
            mvwprintw(window, 0, 0, "Fazendo biscoitos...      ");
            mvwprintw(window, 2, 0, "Faz %d cookies por fornada", skill);
            mvwprintw(window, 4, 0, "Aperte %c para evoluir", actionKeys[id - 1]);

        case GameStats::NOT_PURCHASED:
            mvwprintw(window, 0, 0, "Funcionario nao contratado");
            mvwprintw(window, 4, 0, "Aperte %c para comprar", actionKeys[id - 1]);
        default:
            break;
    }
}

void CookGUI::keyboardHandler(char key) {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};
    if (key == actionKeys[id - 1] || key == actionKeys[id - 1] + 32) {
        switch (status) {
            case 0:
                status = 1;
                break;
            default:
                skill++;
                break;
        }
    }
}