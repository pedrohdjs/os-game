#include "./cooker.hpp"

Cooker::GUI::GUI(Cooker& cooker, int id)
    : BorderedWindow(std::string("Funcionario " + std::to_string(id)), 11, 30,
                     18, 35 * (id - 1) + ((GameStats::WINDOW_WIDTH - 35 * 4) / 2)),
      cooker{cooker} {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda

    width -= 2;
    height -= 2;

    setup();
}

void Cooker::GUI::setup() {
    BorderedWindow::setup();

    //Desenha o funcionario
    mvwprintw(window, 6, 1, "O");
    mvwprintw(window, 7, 0, "/|\\");
    mvwprintw(window, 8, 0, "/ \\     [");
    mvwprintw(window, 8, width - 1, "]s");
}

void Cooker::GUI::drawProgressBar() {
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * cooker.progress);

    wmove(window, 8, 9);
    for (int i = 0; i < maxWidth; i++) {
        if (i < progressWidth) {
            waddch(window, '=');
        } else {
            waddch(window, ' ');
        }
    }
}

void Cooker::GUI::draw() {
    drawInfo();
    if (cooker.status == GameStats::BUSY) {
        drawProgressBar();
    }
}

void Cooker::GUI::onRefresh() {
    cooker.engine.logic();
}

void Cooker::GUI::drawInfo() {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};

    switch (cooker.status) {
        case GameStats::AVAILABLE:
            mvwprintw(window, 0, 0, "Funcionario disponivel      ");
            mvwprintw(window, 2, 0, "Faz %d cookies por fornada  ", cooker.skill);
            mvwprintw(window, 4, 0, "Aperte %c para evoluir      ", actionKeys[cooker.id - 1]);
            break;

        case GameStats::BUSY:
            mvwprintw(window, 0, 0, "Fazendo biscoitos...        ");
            mvwprintw(window, 2, 0, "Faz %d cookies por fornada  ", cooker.skill);
            mvwprintw(window, 4, 0, "Aperte %c para evoluir      ", actionKeys[cooker.id - 1]);
            break;
			
        case GameStats::NOT_PURCHASED:
            mvwprintw(window, 0, 0, "Funcionario nao contratado  ");
            mvwprintw(window, 2, 0, "Compre por %d cookies       ", cooker.id*5);
            mvwprintw(window, 4, 0, "Aperte %c para comprar      ", actionKeys[cooker.id - 1]);
            break;
        case GameStats::WAITING:
            mvwprintw(window, 0, 0, "Esperando um forno...       ");
            mvwprintw(window, 2, 0, "Faz %d cookies por fornada  ", cooker.skill);
            // Evolução custa (skill+1)*3, como fazer caber?
            mvwprintw(window, 4, 0, "Aperte %c para evoluir      ", actionKeys[cooker.id - 1]);
            break;
            
        default:
            break;
    }
}