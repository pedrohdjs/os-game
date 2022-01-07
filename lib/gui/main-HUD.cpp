#include "./main-HUD.hpp"

MainHUD::MainHUD(WINDOW* parentWindow)
    : BorderedWindow("", 7, GameStats::WINDOW_WIDTH / 2, GameStats::WINDOW_HEIGHT - 10, (GameStats::WINDOW_WIDTH / 2) / 2 - 2, parentWindow) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    width -= 2;
    height -= 2;
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
    //Ignora os caracteres '│', '│', [', ']' e 'X'
    int maxProgressWidth = (width - 5) / 2 + 1;

    //Limpa a barra de progresso
    wmove(window, height, 2);
    for (int i = 0; i < maxProgressWidth; i++) {
        wprintw(window, " ");
    }

    wmove(window, height, width / 2 + 2);
    for (int i = 0; i < maxProgressWidth; i++) {
        wprintw(window, " ");
    }

    //Calcula o começo e o fim dos '='
    float progress = (float)GameStats::getNumberOfCookies() / (float)GameStats::target;

    progress = (progress >= 1.0) ? 1 : progress;
    progress = (progress <= -1.0) ? -1 : progress;

    int progressWidth = abs((int)(progress * (float)maxProgressWidth));

    int start, end;

    if (progress > 0) {
        start = width / 2 + 2;
        end = start + progressWidth;
    } else {
        start = (width / 2 + 1) - progressWidth;
        end = width / 2 + 1;
    }

    //Imprime os '='
    char printedChar = '\0';

    for (int i = start; i < end; i++) {
        if (i == start && progress < 0) {
            printedChar = '<';
        } else if (i == end - 1 && progress > 0) {
            printedChar = '>';
        } else {
            printedChar = '=';
        }
        mvwprintw(window, height, i, "%c", printedChar);
    }
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
