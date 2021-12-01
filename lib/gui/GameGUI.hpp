#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <string>

#include "./main/main-window.hpp"

class GameGUI {
    private:
        MainWindow* mainWindow;

        int refreshRate;
        int delaySize;

    public:
        /**
        * Construtor da janela do programa
        * @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
        */
        GameGUI(int refreshRate);
        
        /**
         * Destrutor da janela
         */
        ~GameGUI();

        /**
         * Inicializa a janela com o seu setup e começa a desenhar
         */
        void show();

    private:
        /**
        * Realiza uma refresh das janelas e de sua suas sub janelas
        */
        void refresh();
};