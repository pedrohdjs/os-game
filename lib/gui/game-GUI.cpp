#include "./game-GUI.hpp"

GameGUI::GameGUI(int refreshRate) {
    GameStats::setFrameRate(refreshRate);
    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    clear();
    nodelay(stdscr, true);
    //Inicializa a janela principal
    mainWindow = new BorderedWindow("Jogo de SO", GameStats::WINDOW_HEIGHT, GameStats::WINDOW_WIDTH, 0, 0);

    //Inicializa os outros componentes
    mainHUD = new MainHUD();

    for (int i = 1; i <= 4; i++) {
        GameStats::Ovens.push_back(new Oven(i));
        GameStats::Cooks.push_back(new Cooker(i));
    }

    Customer::start();
}

GameGUI::~GameGUI() {
    for (int i = 0; i < 4; i++) {
        delete GameStats::Ovens[i];
        delete GameStats::Cooks[i];
    }
    delete mainHUD;
    delete mainWindow;

    endwin();
}

void GameGUI::show() {
    
    for (auto& cook : GameStats::Cooks) {
        cook->start();
    }

    for (auto& oven : GameStats::Ovens) {
        oven->start();
    }
	
    std::thread drawer(&GameGUI::refresh, this);
    std::thread keyboardListener(&GameGUI::keyboardHandler, this);

    GameStats::addThread();
    GameStats::addThread();

    keyboardListener.detach();
    drawer.join();

}

void GameGUI::refresh() {
    while (GameStats::isRunning()) {
        //clear();
        mainWindow->refresh();
        mainHUD->refresh();

        for (auto& cook : GameStats::Cooks) {
            cook->interface.refresh();
        }

        for (auto& oven : GameStats::Ovens) {
            oven->interface.refresh();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(GameStats::getFrameRateDelay()));
    }

    GameStats::removeThread();
}

void GameGUI::keyboardHandler() {
    char key = '\0';
    while (GameStats::isRunning()) {
        key = wgetch(stdscr);
        if (key != ERR) {
            if (key == 27) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    GameStats::removeThread();
}
