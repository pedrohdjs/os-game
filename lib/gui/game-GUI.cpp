#include "./game-GUI.hpp"

GameGUI::GameGUI(int refreshRate) {
    GameStats::setFrameRate(refreshRate);
    //Inicializações da ncurses
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    clear();

    //Inicializa a janela principal
    mainWindow = new BorderedWindow("Jogo de SO", GameStats::WINDOW_HEIGHT - 1, GameStats::WINDOW_WIDTH - 1, 0, 0);

    //Inicializa os outros componentes
    mainHUD = new MainHUD(mainWindow->window);

    for (int i = 1; i <= 4; i++) {
        GameStats::Ovens.push_back(new Oven(i, mainWindow->window));
        GameStats::Cooks.push_back(new Cooker(i, mainWindow->window));
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

    Customers::start();
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
    mainWindow->setup();
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

    setup();
    refresh();
    doupdate();

    GameStats::removeThread();
}

void GameGUI::endGameScreen() {
    clear();
    std::stringstream message;

    wprintwc(stdscr, "Fim de Jogo!", GameStats::CURRENT_HEIGHT / 2 - 5, false);

    if (GameStats::victory) {
        wprintwc(stdscr, "Parabéns você venceu!", GameStats::CURRENT_HEIGHT / 2 - 3, false);
        wprintwc(stdscr, "Agora você comer todos os seus biscoitos! :)", GameStats::CURRENT_HEIGHT / 2 - 2, false);
    } else {
        wprintwc(stdscr, "Você perdeu", GameStats::CURRENT_HEIGHT / 2 - 3, false);
        wprintwc(stdscr, ":(", GameStats::CURRENT_HEIGHT / 2 - 2, false);
    }

    wprintwc(stdscr, "Estatisticas:", GameStats::CURRENT_HEIGHT / 2, false);

    message << "Biscoitos (cozinheiros): " << GameStats::totalNumberOfCookies - GameStats::totalNumberOfCookiesUser;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 1, false);
    message.str("");

    message << "Biscoitos \n (você): " << GameStats::totalNumberOfCookiesUser;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 2, false);
    message.str("");

    int numberOfCustomers =
        GameStats::victory
            ? GameStats::totalNumberOfCustomers
            : GameStats::totalNumberOfCustomers - 1000;

    message << "Clientes satisfeitos: " << numberOfCustomers;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 3, false);
    message.str("");

    message << "Pressione qualquer tecla para sair";
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 5, false);
    message.str("");

    wrefresh(stdscr);
}

void GameGUI::keyboardHandler() {
    int key = '\0';
    char pastkey = '\0';
    MEVENT event;
    while (GameStats::isRunning()) {
        timeout(10);
        key = getch();

        if (key == ' ' && pastkey != ' ') {
            flushinp();
            GameStats::updateNumberOfCookies(1);
            GameStats::totalNumberOfCookiesUser++;
        }

        if (key != ERR) {
            for (auto& oven : GameStats::Ovens) {
                oven->engine.keyboardHandler(key);
            }

            for (auto& cook : GameStats::Cooks) {
                cook->engine.keyboardHandler(key);
            }
        }
        flushinp();
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    flushinp();
    GameStats::removeThread();
}
