#include "./GameGUI.hpp"

GameGUI::GameGUI(int refreshRate, int target) {
    this->refreshRate = refreshRate;
    this->target = target;

    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    nocbreak();
    curs_set(0);

    //Cálculo do tamanho do delay entre as atualizações da GUI
    delaySize = 1000 / refreshRate;  // 1s/fps

    //Inicializa a janela principal
    this->mainWindow = new BorderedWindow("Jogo de SO", WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);

    //Inicializa os outros componentes
    this->mainHUD = new MainHUD(100);

    refresh();
}

GameGUI::~GameGUI() {
    endwin();
}

void GameGUI::show() {
    //cria uma thread para redesenhar as sub janelas
    std::thread drawer(&GameGUI::refresh,this);
    drawer.detach();
}

void GameGUI::refresh() {
    while (true) {
        mainWindow->refresh();
        mainHUD->refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(delaySize));
    }
}