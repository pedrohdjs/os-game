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

    this->ovens = vector<class OvenGUI*>();
    for(int i = 1; i<=4; i++) {
        this->ovens.push_back(new OvenGUI(i));
        this->cooks.push_back(new CookGUI(i));
    }

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
    float ovensProgress = 0;
    while (true) {
        //TODO: obter dados do jogo
        mainWindow->refresh();
        mainHUD->refresh();
        for(int i = 0; i<4; i++) {
            ovens[i]->setProgress(ovensProgress);
            ovens[i]->refresh();
            cooks[i]->refresh();
            
        }
        ovensProgress += 0.1;
        if(ovensProgress > 1.01) ovensProgress = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(delaySize));
    }
}

BorderedWindow* GameGUI::getMainWindow(){
    return this->mainWindow;
}

MainHUD* GameGUI::getMainHUD(){
    return this->mainHUD;
}

vector<class OvenGUI*> GameGUI::getOvens(){
    return this->ovens;
}

vector<class CookGUI*> GameGUI::getCooks(){
    return this->cooks;
};