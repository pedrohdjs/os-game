#include "./MainHUD.hpp"

MainHUD::MainHUD(int target)
    : BorderedWindow("", 7, GameStats::WINDOW_WIDTH / 2, GameStats::WINDOW_HEIGHT - 10, (GameStats::WINDOW_WIDTH / 2) / 2) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    this->width -= 2;
    this->height -= 2;

    this->target = target;
    this->score = 0;
    this->setup();
}

void MainHUD::setup() {
    BorderedWindow::setup();

    //Desenha o esqueleto da barra de progresso
    wprintwc(window, string("Chegue a " + to_string(target) + " cookies para vencer"), 0);
    mvwprintw(window, height - 1, 0, "[");
    mvwprintw(window, height - 1, width / 2, "X");
    mvwprintw(window, height - 1, width - 1, "]");
}

void MainHUD::refresh() {
    BorderedWindow::refresh();
}

void MainHUD::draw() {
    drawProgressBar();
    drawScore();
}

void MainHUD::drawProgressBar() {
    //Ignora os caracteres '[', ']' e 'X'
    int maxProgressWidth = (width - 3) / 2;

    //Limpa a barra de progresso
    wmove(window, height - 1, 1);
    for (int i = 0; i < maxProgressWidth; i++) {
        wprintw(window, " ");
    }
    wmove(window, height - 1, width / 2 + 1);
    for (int i = 0; i < maxProgressWidth; i++) {
        wprintw(window, " ");
    }

    //Calcula o começo e o fim dos '='
    float progress = (float)score / (float)target;
    int progressWidth = abs((int)(progress * (float)maxProgressWidth));
    int start, end;
    if (progress > 0) {
        start = width / 2 + 1;
        end = start + progressWidth;
    } else {
        start = width / 2 - progressWidth;
        end = width / 2;
    }

    //Imprime os '='
    for (int i = start; i < end; i++) {
        mvwprintw(window, height - 1, i, "=");
    }
}

void MainHUD::drawScore() {
    string s;

    if (score > 0) {
        s = "Você tem " + to_string(score) + " cookies";
    } else {
        s = "Você tem " + to_string(abs(score)) + " clientes esperando";
    }

    wclearline(window, 2);
    wprintwc(window, s, 2);
}

void MainHUD::setScore(int score) {
    this->score = score;
}