#include "./oven.hpp"


Oven::GUI::GUI(Oven& oven, int id, WINDOW* parentWindow)
    : BorderedWindow(std::string("Forno " + std::to_string(id)), 15, 30, 2, 35 * (id - 1) + ((GameStats::WINDOW_WIDTH - 35 * 4) / 2) + 2, parentWindow),
      oven{oven} {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    width -= 2;
    height -= 2;

}


void Oven::GUI::setup() {
    BorderedWindow::setup();

    //Desenha o esqueleto do forno
    mvwprintw(window, 9, 3, "/ \\");
    mvwprintw(window, 10, 3, "| |");
    mvwprintw(window, 11, 1, "|-----|");
    mvwprintw(window, 12, 1, "|     |");
    mvwprintw(window, 13, 1, "|-----| [");
    mvwprintw(window, 13, width , "]");
}

void Oven::GUI::draw() {

    drawInfo();
    drawProgressBar();
    if (oven.status == GameStats::BUSY) {
        drawSmoke();
    }
}


void Oven::GUI::drawInfo() {
    switch (oven.status) {
        case GameStats::AVAILABLE:
            mvwprintw(window, 2, 1, "Forno disponível           ");
            mvwprintw(window, 3, 1, "Aperte %d para evoluir       ", oven.id);
            mvwprintw(window, 4, 1, "Custo: 10 Cookies          ");
            mvwprintw(window, 5, 1, "Capacidade: %d cookies     ", oven.capacity);
            break;

        case GameStats::BUSY:
            mvwprintw(window, 2, 1, "Forno ocupado              ");
            mvwprintw(window, 5, 1, "Assando cookies...  %d/%d  ", oven.currBakingCookies, oven.capacity);
            mvwprintw(window, 12, 4, "O");
            break;

        case GameStats::NOT_PURCHASED: 
            mvwprintw(window, 2, 1, "Forno indisponível         ");
            mvwprintw(window, 3, 1, "Compre por %d cookies      ", (oven.id - 1)*10);
            mvwprintw(window, 6, 1, "Aperte %d para comprar     ", oven.id);
            mvwprintw(window, 12, 4, "X");
            break;

        default:
            break;
    }
}


void Oven::GUI::drawProgressBar() {
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * oven.progress);

    wmove(window, 13, 10);
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
    mvwprintw(window, 8, 4, smokeState >= 1 && smokeState <= 3 ? "O" : " ");
    mvwprintw(window, 7, 5, smokeState >= 2 && smokeState <= 4 ? "O" : " ");
    mvwprintw(window, 6, 4, smokeState >= 3 && smokeState <= 5 ? "O" : " ");
}

