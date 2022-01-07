#include "./cooker.hpp"

Cooker::GUI::GUI(Cooker& cooker, int id, WINDOW* parentWindow)
    : BorderedWindow(std::string("Cozinheiro " + std::to_string(id)), 11, 30,
                     18, 35 * (id - 1) + ((GameStats::WINDOW_WIDTH - 35 * 4) / 2) + 2, parentWindow),
      cooker{cooker} {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda

    width -= 2;
    height -= 2;
}

void Cooker::GUI::setup() {
    BorderedWindow::setup();

    //Desenha o funcionario
    mvwprintw(window, 7, 2, "O");
    mvwprintw(window, 8, 1, "/|\\");
    mvwprintw(window, 9, 1, "/ \\     [");
    mvwprintw(window, 9, width, "]");
}

void Cooker::GUI::drawProgressBar() {
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * cooker.progress);

    wmove(window, 9, 10);
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
    drawProgressBar();
}

void Cooker::GUI::drawInfo() {
    char actionKeys[4] = {'q', 'w', 'e', 'r'};

    switch (cooker.status) {
        case GameStats::NOT_PURCHASED:
            mvwprintw(window, 1, 1, "Cozinheiro nao contratado");
            mvwprintw(window, 3, 1, "Compre por %d cookies    ", cooker.id * 5);
            mvwprintw(window, 5, 1, "Aperte %c para comprar", actionKeys[cooker.id - 1]);
            break;

        case GameStats::AVAILABLE:
            mvwprintw(window, 1, 1, "Cozinheiro disponível");
            mvwprintw(window, 3, 1, "Faz %d cookies por fornada", cooker.skill);
            if (cooker.skill == (GameStats::Ovens[0]->engine.getMaxCapacity())) {
                mvwprintw(window, 5, 1, "Cozinheiro exemplar!");
            } else {
                mvwprintw(window, 5, 1, "Aperte %c para evoluir", actionKeys[cooker.id - 1]);
                mvwprintw(window, 6, 1, "Custo: %d cookies", (cooker.skill + 1) * 3);
            }
            break;
        case GameStats::RESTING:
            mvwprintw(window, 1, 1, "Cozinheiro descansando   ");
            mvwprintw(window, 3, 1, "Faz %d cookies por fornada", cooker.skill);
            if (cooker.skill == (GameStats::Ovens[0]->engine.getMaxCapacity())) {
                mvwprintw(window, 5, 1, "Cozinheiro exemplar!    ");
            } else {
                mvwprintw(window, 5, 1, "Aperte %c para evoluir   ", actionKeys[cooker.id - 1]);
                mvwprintw(window, 6, 1, "Custo: %d cookies        ", (cooker.skill + 1) * 3);
            }
            break;

        case GameStats::BUSY:
            mvwprintw(window, 1, 1, "Fazendo biscoitos...     ");
            mvwprintw(window, 3, 1, "Faz %d cookies por fornada", cooker.skill);
            if (cooker.skill == (GameStats::Ovens[0]->engine.getMaxCapacity())) {
                mvwprintw(window, 5, 1, "Cozinheiro exemplar!  ");
            } else {
                mvwprintw(window, 5, 1, "Aperte %c para evoluir", actionKeys[cooker.id - 1]);
                mvwprintw(window, 6, 1, "Custo: %d cookies     ", (cooker.skill + 1) * 3);
            }
            break;

        case GameStats::WAITING:
            mvwprintw(window, 1, 1, "Esperando um forno...     ");
            mvwprintw(window, 3, 1, "Faz %d cookies por fornada", cooker.skill);
            if (cooker.skill == (GameStats::Ovens[0]->engine.getMaxCapacity())) {
                mvwprintw(window, 5, 1, "Cozinheiro exemplar!  ");
            } else {
                mvwprintw(window, 5, 1, "Aperte %c para evoluir", actionKeys[cooker.id - 1]);
                mvwprintw(window, 6, 1, "Custo: %d cookies     ", (cooker.skill + 1) * 3);
            }
            break;

        default:
            break;
    }
}