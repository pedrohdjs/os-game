#include "./oven.hpp"


Oven::GUI::GUI(Oven& oven, int id)
    : BorderedWindow(std::string("Forno " + std::to_string(id)), 15, 30, 2, 35 * (id - 1) + ((GameStats::WINDOW_WIDTH - 35 * 4) / 2)),
      oven{oven} {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    width -= 2;
    height -= 2;

    setup();
}


void Oven::GUI::setup() {
    BorderedWindow::setup();

    //Desenha o esqueleto do forno
    mvwprintw(window, 8, 2, "/ \\");
    mvwprintw(window, 9, 2, "| |");
    mvwprintw(window, 10, 0, "|-----|");
    mvwprintw(window, 11, 0, "|     |");
    mvwprintw(window, 12, 0, "|-----| [");
    mvwprintw(window, 12, width - 1, "]");
}

void Oven::GUI::draw() {
    drawInfo();
    if (oven.status == GameStats::BUSY) {
        drawProgressBar();
        drawSmoke();
    }
}


void Oven::GUI::drawInfo() {
    switch (oven.status) {
        case GameStats::AVAILABLE:
            mvwprintw(window, 0, 0, "Forno disponível           ");
            mvwprintw(window, 2, 0, "Aperte %d para evoluir       ", oven.id);
            mvwprintw(window, 3, 0, "Custo: 10 Cookies          ");
            mvwprintw(window, 4, 0, "Capacidade: %d cookies     ", oven.capacity);
            break;

        case GameStats::BUSY:
            mvwprintw(window, 0, 0, "Forno ocupado              ");
            mvwprintw(window, 4, 0, "Assando cookies...  %d/%d  ", oven.currBakingCookies, oven.capacity);
            mvwprintw(window, 11, 3, "O");
            break;

        case GameStats::NOT_PURCHASED: 
            mvwprintw(window, 0, 0, "Forno indisponível         ");
            mvwprintw(window, 2, 0, "Compre por %d cookies      ", (oven.id - 1)*10);
            mvwprintw(window, 4, 0, "Aperte %d para comprar     ", GameStats::getNumberOfThreads());
            mvwprintw(window, 11, 3, "X");
            break;

        default:
            break;
    }
}


void Oven::GUI::drawProgressBar() {
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * oven.progress);
    wmove(window, 12, 9);
    for (int i = 0; i < maxWidth; i++) {
        if (i < progressWidth) {
            waddch(window, '=');
        } else {
            waddch(window, ' ');
        }
    }
}

void Oven::GUI::drawSmoke() {
    if (oven.progress == 0) return;
    int smokeState = (int)6 * oven.progress;
    mvwprintw(window, 7, 3, smokeState >= 1 && smokeState <= 3 ? "O" : " ");
    mvwprintw(window, 6, 4, smokeState >= 2 && smokeState <= 4 ? "O" : " ");
    mvwprintw(window, 5, 3, smokeState >= 3 && smokeState <= 5 ? "O" : " ");
}

