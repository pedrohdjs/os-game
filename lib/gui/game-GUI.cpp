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
    mainWindow = new BorderedWindow("Thread Cookies", GameStats::WINDOW_HEIGHT - 1, GameStats::WINDOW_WIDTH - 1, 0, 0);

    //Inicializa a hud de dados
    mainHUD = new MainHUD(mainWindow->window);

    //adiciona os cozinheiros e os fornos na GUI
    for (int i = 1; i <= 4; i++) {
        GameStats::Ovens.push_back(new Oven(i, mainWindow->window));
        GameStats::Cooks.push_back(new Cooker(i, mainWindow->window));
    }

    GameStats::detectTerminalResize();
}

GameGUI::~GameGUI() {
    delete mainHUD;
    delete mainWindow;

    endwin();
}

void GameGUI::detectMinimumTerminalSize() {
    while (GameStats::CURRENT_WIDTH < GameStats::WINDOW_WIDTH || GameStats::CURRENT_HEIGHT < GameStats::WINDOW_HEIGHT) {
        GameStats::detectTerminalResize();
        terminalSizeScreen();

        doupdate();

        std::this_thread::sleep_for(std::chrono::milliseconds(GameStats::getFrameRateDelay()));
    }

    flushinp();
    clear();
    ::refresh();
}

void GameGUI::show() {
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

void GameGUI::terminalSizeScreen() {
    std::stringstream message;

    wprintwc(stdscr, "Por favor redimensione seu terminal ou altere o tamanho da fonte!!", GameStats::CURRENT_HEIGHT / 2 - 1, false);

    message << "Tamanho mínimo: " << GameStats::WINDOW_WIDTH << " X " << GameStats::WINDOW_HEIGHT;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2, false);
    message.str("");

    message << "Tamanho atual: " << GameStats::CURRENT_WIDTH << " X " << GameStats::CURRENT_HEIGHT;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 1, false);

    wnoutrefresh(stdscr);
}

void GameGUI::startGameScreen() {
    clear();
    std::stringstream message;

    wprintwc(stdscr, "========== Thread Cookies ==========", GameStats::CURRENT_HEIGHT / 2 - 5, false);
    wprintwc(stdscr, "Finalmente o tão esperado dia chegou, você conseguiu abrir sua própria confeitaria!!", GameStats::CURRENT_HEIGHT / 2 - 3, false);

    wprintwc(stdscr, "Contrate funcionários, compre novos fornos e tente atingir 1000 cookies ", GameStats::CURRENT_HEIGHT / 2 - 2, false);
    wprintwc(stdscr, "antes que uma horda de clientes famintos ataque você!", GameStats::CURRENT_HEIGHT / 2 - 1, false);

    wprintwc(stdscr, "============= Comandos =============", GameStats::CURRENT_HEIGHT / 2, false);
    wprintwc(stdscr, "Pressione 1, 2, 3, 4 para comprar e evoluir os fornos", GameStats::CURRENT_HEIGHT / 2 + 2, false);
    wprintwc(stdscr, "Pressione q, w, e, r para contratar e melhorar funcionários", GameStats::CURRENT_HEIGHT / 2 + 3, false);
    wprintwc(stdscr, "Pressione SPACE para produzir 1 cookie por vez", GameStats::CURRENT_HEIGHT / 2 + 4, false);
    wprintwc(stdscr, "====================================", GameStats::CURRENT_HEIGHT / 2 + 6, false);
    wprintwc(stdscr, "Pressione qualquer tecla para continuar", GameStats::CURRENT_HEIGHT / 2 + 8, false);

    wrefresh(stdscr);
    waitInput();
}

void GameGUI::endGameScreen() {
    clear();
    ::refresh();

    std::stringstream message;

    wprintwc(stdscr, "=========== Fim de Jogo! ===========", GameStats::CURRENT_HEIGHT / 2 - 6, false);

    if (GameStats::victory) {
        wprintwc(stdscr, "Parabéns você venceu!", GameStats::CURRENT_HEIGHT / 2 - 4, false);
        wprintwc(stdscr, "Agora você pode comer todos os seus biscoitos! :)", GameStats::CURRENT_HEIGHT / 2 - 3, false);
    } else {
        wprintwc(stdscr, "Você perdeu", GameStats::CURRENT_HEIGHT / 2 - 4, false);
        wprintwc(stdscr, ":(", GameStats::CURRENT_HEIGHT / 2 - 3, false);
    }

    wprintwc(stdscr, "Estatísticas:", GameStats::CURRENT_HEIGHT / 2 - 1, false);

    message << "Biscoitos (cozinheiros): " << GameStats::totalNumberOfCookies - GameStats::totalNumberOfCookiesUser;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 1, false);
    message.str("");

    message << "Biscoitos (você): " << GameStats::totalNumberOfCookiesUser;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 2, false);
    message.str("");

    int numberOfCustomers =
        GameStats::victory
            ? GameStats::totalNumberOfCustomers
            : GameStats::totalNumberOfCustomers - 1000;

    message << "Clientes satisfeitos: " << numberOfCustomers;
    wprintwc(stdscr, message.str(), GameStats::CURRENT_HEIGHT / 2 + 3, false);
    message.str("");

    wprintwc(stdscr, "==================================", GameStats::CURRENT_HEIGHT / 2 + 5, false);
    wprintwc(stdscr, "Pressione qualquer tecla para sair", GameStats::CURRENT_HEIGHT / 2 + 7, false);

    wrefresh(stdscr);
    waitInput();
}

void GameGUI::waitInput() {
    flushinp();
    timeout(-1);
    getch();
    flushinp();
}

void GameGUI::keyboardHandler() {
    int key = '\0';

    while (GameStats::isRunning()) {
        timeout(10);
        key = getch();

        if (key != ERR) {
            if (key == ' ') {
                flushinp();
                GameStats::updateNumberOfCookies(1);
                GameStats::totalNumberOfCookiesUser++;
            }

            for (auto& oven : GameStats::Ovens) {
                oven->engine.keyboardHandler(key);
            }

            for (auto& cook : GameStats::Cooks) {
                cook->engine.keyboardHandler(key);
            }
        }

        flushinp();
    }

    flushinp();
    GameStats::removeThread();
}
