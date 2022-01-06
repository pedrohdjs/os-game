#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include "./bordered-window.hpp"
#include "./main-HUD.hpp"
#include "../oven/oven.hpp"
#include "../cooker/cooker.hpp"
#include "../utils/game-stats.hpp"
#include "../utils/customer.hpp"

/**
 * @brief Representa e agrega todos os componentes visuais do jogo.
 */
class GameGUI {
    private:
        BorderedWindow* mainWindow; // Janela principal
        MainHUD* mainHUD; //HUD principal com informações de progresso

        //Thread responsável por atualizar a janela
        void refresh();

    public:
        /**
        * Construtor da janela do programa
        * @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
        * @param target indica o número de pontos que deve ser alcançado ao fim do jogo
        */
        GameGUI(int refreshRate);
        
        //Destrutor da janela
        ~GameGUI();

        //Inicializa a janela com o seu setup e começa a desenhar
        void show();

        void keyboardHandler();

};