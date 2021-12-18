#include "./GameGUI.hpp"

GameGUI::GameGUI(int refreshRate, int target) {
    this->refreshRate = refreshRate;
    this->target = target;

    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();

    //Cálculo do tamanho do delay entre as atualizações da GUI
    delaySize = 1000 / refreshRate;  // 1s/fps

    //Inicializa a janela principal
    this->mainWindow = new BorderedWindow("Jogo de SO", GameStats::WINDOW_HEIGHT, GameStats::WINDOW_WIDTH, 0, 0);

    //Inicializa os outros componentes
    this->mainHUD = new MainHUD(100);

    for (int i = 1; i <= 4; i++) {
        ovens.push_back(new OvenGUI(i));
        cooks.push_back(new CookGUI(i));
    }
}

GameGUI::~GameGUI() {
    endwin();
}

void GameGUI::show() {

    //cria uma thread para redesenhar as sub janelas
    std::thread drawer(&GameGUI::refresh, this);
    std::thread keyboardListener(&GameGUI::keyboardHandler, this);
    keyboardListener.detach();
    drawer.join();
}

void GameGUI::refresh() {

    mainWindow->refresh();
    mainHUD->refresh();
    
	for (auto& cook : cooks) {
    	cook->start();
    }
	
	for (auto& oven : ovens) {
    	oven->start();
    }

    while (GameStats::isRunning()) {

        //TODO: obter dados do jogo
        mainWindow->refresh();
        mainHUD->refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(delaySize));
    }
}

void GameGUI::keyboardHandler() {
    char key = '\0';
    while (true) {
        key = getch();

        for (auto& oven : ovens) {
            oven->keyboardHandler(key);
        }

        for (auto& cook : cooks) {
            cook->keyboardHandler(key);
        }
    }
}

BorderedWindow* GameGUI::getMainWindow() {
    return mainWindow;
}

MainHUD* GameGUI::getMainHUD() {
    return mainHUD;
}

vector<class OvenGUI*> GameGUI::getOvens() {
    return ovens;
}

vector<class CookGUI*> GameGUI::getCooks() {
    return cooks;
};