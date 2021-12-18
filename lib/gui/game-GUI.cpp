#include "./game-GUI.hpp"

GameGUI::GameGUI(int refreshRate, int target) {
    GameStats::setFrameRate(refreshRate);
    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();

    //Inicializa a janela principal
    mainWindow = new BorderedWindow("Jogo de SO", GameStats::WINDOW_HEIGHT, GameStats::WINDOW_WIDTH, 0, 0);

    //Inicializa os outros componentes
    mainHUD = new MainHUD(100);

    for (int i = 1; i <= 4; i++) {
        GameStats::Ovens.push_back(new Oven(i));
        GameStats::Cooks.push_back(new Cooker(i));
    }
}

GameGUI::~GameGUI() {
    for (int i = 1; i <= 4; i++) {
        delete GameStats::Ovens[i];
        delete GameStats::Cooks[i];
    }
    delete mainHUD;
    delete mainWindow;

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

    for (auto& cook : GameStats::Cooks) {
        cook->start();
    }

    for (auto& oven : GameStats::Ovens) {
        oven->start();
    }

    while (GameStats::isRunning()) {
        mainWindow->refresh();
        mainHUD->refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(GameStats::getFrameRateDelay()));
    }
}

void GameGUI::keyboardHandler() {
    char key = '\0';
    while (GameStats::isRunning()) {
        key = getch();
		
        if (key == ':') {
            GameStats::end();
            return;
        }

        for (auto& oven : GameStats::Ovens) {
            oven->engine.keyboardHandler(key);
        }

        for (auto& cook : GameStats::Cooks) {
            cook->engine.keyboardHandler(key);
        }
    }
}
