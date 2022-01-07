#include "./game-GUI.hpp"

GameGUI::GameGUI(int refreshRate) {
    GameStats::setFrameRate(refreshRate);
    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    clear();
    //nodelay(stdscr, true);
    //Inicializa a janela principal
    mainWindow = new BorderedWindow("Jogo de SO", GameStats::WINDOW_HEIGHT - 1, GameStats::WINDOW_WIDTH - 1, 0, 0);

    //Inicializa os outros componentes
    mainHUD = new MainHUD();

    for (int i = 1; i <= 4; i++) {
        GameStats::Ovens.push_back(new Oven(i));
        GameStats::Cooks.push_back(new Cooker(i));
    }
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
    int cols, rows;

    while (GameStats::CURRENT_WIDTH < GameStats::WINDOW_WIDTH || GameStats::CURRENT_HEIGHT < GameStats::WINDOW_HEIGHT) {
        terminalSizeScreen();

        GameStats::detectTerminalResize();
        doupdate();
        std::this_thread::sleep_for(std::chrono::milliseconds(GameStats::getFrameRateDelay()));
    }

    for (auto& cook : GameStats::Cooks) {
        cook->start();
    }

    for (auto& oven : GameStats::Ovens) {
        oven->start();
    }

    std::thread drawer(&GameGUI::refreshLoop, this);
    std::thread keyboardListener(&GameGUI::keyboardHandler, this);

    GameStats::addThread();
    GameStats::addThread();

    drawer.detach();
    keyboardListener.join();
}

void GameGUI::refresh() {
    mainWindow->refresh();
    mainHUD->refresh();

    for (auto& cook : GameStats::Cooks) {
        cook->interface.refresh();
    }

    for (auto& oven : GameStats::Ovens) {
        oven->interface.refresh();
    }
}

void GameGUI::setup() {
    //mainWindow->setup();
    mainHUD->setup();

    for (auto& cook : GameStats::Cooks) {
        cook->interface.setup();
    }

    for (auto& oven : GameStats::Ovens) {
        oven->interface.setup();
    }
}

void GameGUI::terminalSizeScreen() {
    std::stringstream message;

    wprintwc(stdscr, "Por favor redimensione seu terminal!!", GameStats::CURRENT_HEIGHT / 2 - 1, false);

    message << "Tamanho minimo: " << GameStats::WINDOW_WIDTH << " X " << GameStats::WINDOW_HEIGHT;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2, false);
    message.str("");

    message << "Tamanho atual: " << GameStats::CURRENT_WIDTH << " X " << GameStats::CURRENT_HEIGHT;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 1, false);

    wnoutrefresh(stdscr);
}

void GameGUI::refreshLoop() {
    clear();
    while (GameStats::isRunning()) {
        GameStats::detectTerminalResize();

        if (GameStats::CURRENT_WIDTH < GameStats::WINDOW_WIDTH || GameStats::CURRENT_HEIGHT < GameStats::WINDOW_HEIGHT) {
            terminalSizeScreen();
        } else {
            setup();
            refresh();
        }
        doupdate();
        std::this_thread::sleep_for(std::chrono::milliseconds(GameStats::getFrameRateDelay()));
    }

    GameStats::removeThread();
}

void GameGUI::keyboardHandler() {
    int key = '\0';
    while (GameStats::isRunning()) {
        timeout(100);
        key = getch();
        if (key != ERR) {
            for (auto& oven : GameStats::Ovens) {
                oven->engine.keyboardHandler(key);
            }

            for (auto& cook : GameStats::Cooks) {
                cook->engine.keyboardHandler(key);
            }

            if (key == KEY_RESIZE) {
            }
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    GameStats::removeThread();
}
