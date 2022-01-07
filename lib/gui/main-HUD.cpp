#include "./main-HUD.hpp"

MainHUD::MainHUD(WINDOW* parentWindow)
    : BorderedWindow("", 7, GameStats::WINDOW_WIDTH / 2, GameStats::WINDOW_HEIGHT - 10, (GameStats::WINDOW_WIDTH / 2) / 2, parentWindow) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    width -= 2;
    height -= 2;

    //Ignora os caracteres '│', '│', [', ']' e 'X'
    maxProgressWidth = (width - 5) / 2 + 1;
}

void MainHUD::draw() {
    drawStaticComponents();
    drawProgressBar();
    drawScore();
    drawDemand();
}

void MainHUD::drawStaticComponents() {
    //Desenha o esqueleto da barra de progresso
    wprintwc(this, std::string("Chegue a " + std::to_string(GameStats::target) + " cookies para vencer"), 1, false);
    mvwprintw(window, height, 1, "[");
    mvwprintw(window, height, width / 2 + 1, "X");
    mvwprintw(window, height, width, "]");
}

void MainHUD::drawProgressBar() {
    clearProgressBar();
    updateCurrProgress();

    int progressWidth = abs((int)(currProgress * (float)maxProgressWidth));

    //define o inicio e o fim da barra

    int start = (currProgress > 0) ? width / 2 + 2 : (width / 2 + 1) - progressWidth;
    int end = (currProgress > 0) ? start + progressWidth : width / 2 + 1;

    //Imprime os '='
    char printedChar = '=';
    for (int i = start; i < end; i++) {

     	printedChar = '=';
        printedChar = (i == start && currProgress < 0) ? '<' : printedChar;
        printedChar = (i == end - 1 && currProgress > 0) ? '>' : printedChar;

        mvwprintw(window, height, i, "%c", printedChar);
    }
}

void MainHUD::clearProgressBar() {
    wmove(window, height, 2);
    for (int i = 0; i < maxProgressWidth; i++) {
        wprintw(window, " ");
    }

    wmove(window, height, width / 2 + 2);
    for (int i = 0; i < maxProgressWidth; i++) {
        wprintw(window, " ");
    }
}

void MainHUD::updateCurrProgress() {
    currProgress = (float)GameStats::getNumberOfCookies() / (float)GameStats::target;

    currProgress = (currProgress >= 1.0) ? 1 : currProgress;
    currProgress = (currProgress <= -1.0) ? -1 : currProgress;
}

void MainHUD::drawScore() {
    std::stringstream s;
    if (GameStats::getNumberOfCookies() >= 0) {
        s << "Cookies: " << GameStats::getNumberOfCookies();
    } else {
        s << "Clientes esperando: " << abs(GameStats::getNumberOfCookies());
    }
    wprintwc(window, s.str().c_str(), 3, true);
}

void MainHUD::drawDemand() {
    std::string s;
    s = " Clientes por segundo: " + std::to_string(Customers::customersRate);
    wprintwc(this, s, 2, true);
}
