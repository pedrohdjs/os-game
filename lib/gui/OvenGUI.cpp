#include "./OvenGUI.hpp"

OvenGUI::OvenGUI(int id)
    : BorderedWindow(string("Forno " + to_string(id)), 15, 30, 2, 35 * (id - 1) + ((GameStats::WINDOW_WIDTH - 35 * 4) / 2)) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->id = id;
    this->status = (id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED;
    this->progress = 1;

    this->setup();
}

void OvenGUI::setup() {
    BorderedWindow::setup();

    //Desenha o esqueleto do forno
    mvwprintw(window, 8, 2, "/ \\");
    mvwprintw(window, 9, 2, "| |");
    mvwprintw(window, 10, 0, "|-----|");
    mvwprintw(window, 11, 0, "|     |");
    mvwprintw(window, 12, 0, "|-----| [");
    mvwprintw(window, 12, width - 1, "]");
}

void OvenGUI::draw() {
    this->drawInfo();
    if (this->status == GameStats::BUSY) {
        this->drawProgressBar();
        this->drawSmoke();
    }
}

void OvenGUI::drawInfo() {
    switch (status) {
        case GameStats::AVAILABLE:
            mvwprintw(window, 0, 0, "Forno disponivel");
            mvwprintw(window, 2, 0, "Aperte %d para assar", id);
            break;

        case GameStats::BUSY:
            mvwprintw(window, 0, 0, "Forno ocupado");
            mvwprintw(window, 4, 0, "Assando cookies...");
            mvwprintw(window, 11, 3, "O");
            break;

        case GameStats::NOT_PURCHASED:
            mvwprintw(window, 0, 0, "Forno indisponivel");
            mvwprintw(window, 2, 0, "Compre por 30 cookies", id);
            mvwprintw(window, 4, 0, "Aperte %d para comprar", id);
            mvwprintw(window, 11, 3, "X");
            break;

        default:
            break;
    }
}

void OvenGUI::drawProgressBar() {
    int maxWidth = width - 10;
    int progressWidth = (int)(maxWidth * progress);
    wmove(window, 12, 9);
    for (int i = 0; i < maxWidth; i++) {
        if (i < progressWidth) {
            waddch(window, '=');
        } else {
            waddch(window, ' ');
        }
    }
}

void OvenGUI::drawSmoke() {
    if (progress == 0) return;
    int smokeState = (int)6 * progress;
    mvwprintw(window, 7, 3, smokeState >= 1 && smokeState <= 3 ? "O" : " ");
    mvwprintw(window, 6, 4, smokeState >= 2 && smokeState <= 4 ? "O" : " ");
    mvwprintw(window, 5, 3, smokeState >= 3 && smokeState <= 5 ? "O" : " ");
}

void OvenGUI::setStatus(int status) {
    this->status = status;
}

void OvenGUI::onRefresh() {
    progress += (progress > 1.0) ? -progress : 0.05;
}

void OvenGUI::setProgress(float progress) {
    this->progress = progress;
    drawProgressBar();
}

void OvenGUI::keyboardHandler(char key) {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};
    if (key == actionKeys[id - 1] || key == actionKeys[id - 1] + 32) {
        switch (status) {
            case 0:
                status = 1;
                break;
        }
    }
}