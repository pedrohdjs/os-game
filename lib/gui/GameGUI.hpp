#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>

#include "./BorderedWindow.hpp"
#include "./MainHUD.hpp"
#include "./OvenGUI.hpp"
#include "./CookGUI.hpp"
#include "./constants.hpp"

/**
 * @brief Representa e agrega todos os componentes visuais do jogo.
 */
class GameGUI {
    private:
        BorderedWindow* mainWindow; // Janela principal
        MainHUD* mainHUD; //HUD principal com informações de progresso
        vector<class OvenGUI*> ovens; //Fornos
        vector<class CookGUI*> cooks; //Funcionários

        int refreshRate; //Taxa de atualização por segundo
        int target; //Pontuação máxima para vencer o jogo
        int delaySize; //Tempo entre cada atualização

        //Thread responsável por atualizar a janela
        void refresh();

    public:
        /**
        * Construtor da janela do programa
        * @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
        * @param target indica o número de pontos que deve ser alcançado ao fim do jogo
        */
        GameGUI(int refreshRate, int target);
        
        //Destrutor da janela
        ~GameGUI();

        //Inicializa a janela com o seu setup e começa a desenhar
        void show();

        //Retorna janela principal
        BorderedWindow* getMainWindow();

        //Retorna HUD principal com informações de progresso
        MainHUD* getMainHUD();

        //Retorna interfaces gráficas de fornos
        vector<class OvenGUI*> getOvens(); 

        //Retorna interfaces gráficas de funcionários
        vector<class CookGUI*> getCooks();
};