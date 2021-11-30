#include "./GameGUI.hpp"

GameGUI::GameGUI(int refreshRate)
: refreshRate{refreshRate} {
    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    nocbreak();

    //Cálculo do tamanho do delay entre as atualizações da GUI
    delaySize = 1000 / refreshRate;  // 1s/fps

    //Inicializa a janela principal
    this->mainWindow = newwin(30,150,0,0);
    box(mainWindow,0,0);


    //Cria as sub janelas

    refresh();
}

GameGUI::~GameGUI() {
    endwin();
}

void GameGUI::show() {
    //cria uma thread para redesenhar as sub janelas
    std::thread drawer(&GameGUI::refresh, this);

    drawer.detach();
}

void GameGUI::refresh() {
    while (true) {
        wrefresh(this->mainWindow);
        std::this_thread::sleep_for(std::chrono::milliseconds(delaySize));
    }
}