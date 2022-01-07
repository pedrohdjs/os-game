#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <sstream>

#include "./bordered-window.hpp"
#include "./main-HUD.hpp"
#include "../oven/oven.hpp"
#include "../cooker/cooker.hpp"
#include "../game-stats/game-stats.hpp"
#include "../customers/customers.hpp"


/**
 * @brief Representa e agrega todos os componentes visuais do jogo.
 */
class GameGUI {
    private:
        BorderedWindow* mainWindow; // Janela principal
        MainHUD* mainHUD; //HUD principal com informações de progresso

        void refreshLoop();
        void terminalSizeScreen();

       public:
        /**
        * Construtor da janela do programa
        * @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
        * @param target indica o número de pontos que deve ser alcançado ao fim do jogo
        */
        GameGUI(int refreshRate);
        
        void refresh();
        //Destrutor da janela
        ~GameGUI();

        //Inicializa a janela com o seu setup e começa a desenhar
        void show();
        void setup();
        void endGameScreen();
        void startGameScreen();

        void keyboardHandler();

};