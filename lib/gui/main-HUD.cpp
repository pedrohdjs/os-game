#include "./main-HUD.hpp"

MainHUD::MainHUD()
    : BorderedWindow("", 7, GameStats::WINDOW_WIDTH / 2, GameStats::WINDOW_HEIGHT - 10, (GameStats::WINDOW_WIDTH / 2) / 2) {
    //Usa apenas a largura e altura da janela para cálculos, ignorando a da borda
    width -= 2;
    height -= 2;

    setup();
}

void MainHUD::draw() {
    drawStaticComponents();
    drawProgressBar();
    drawScore();
    drawDemand();
}

void MainHUD::drawStaticComponents(){
    //Desenha o esqueleto da barra de progresso
    wprintwc(window, std::string("Chegue a " + std::to_string(GameStats::target) + " cookies para vencer"), 0, false);
    mvwprintw(window, height - 1, 0, "[");
    mvwprintw(window, height - 1, width / 2, "X");
    mvwprintw(window, height - 1, width - 1, "]");
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
    float progress = (float) GameStats::getNumberOfCookies() / (float)GameStats::target;
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
    std::string s;
    if (GameStats::getNumberOfCookies() >= 0) {
        s = "Você tem " + std::to_string(GameStats::getNumberOfCookies()) + " cookies";

    } else {
        s = "Você tem " + std::to_string(abs(GameStats::getNumberOfCookies())) + " clientes esperando";
    }

    wprintwc(window, s, 2, false);
}

void MainHUD::drawDemand() {
    std::string s;
    s = " Clientes por segundo: " + std::to_string(Customer::getCustomerRate());
    wprintwc(window, s, 1, false);
}
