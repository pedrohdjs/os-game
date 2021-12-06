#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>

#include "./BorderedWindow.hpp"
#include "./MainHUD.hpp"
#include "./Oven.hpp"
#include "./constants.hpp"

class GameGUI {
    private:
        BorderedWindow* mainWindow;
        MainHUD* mainHUD;
        vector<class Oven*> ovens;

        int refreshRate;
        int target;
        int delaySize;

    public:
        /**
        * Construtor da janela do programa
        * @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
        * @param target indica o número de pontos que deve ser alcançado ao fim do jogo
        */
        GameGUI(int refreshRate, int target);
        
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
        * Obtém as informações do estado atual do jogo e redesenha as janelas e subjanelas
        */
        void refresh();
};