#pragma once

#include <string>

#include "./bordered-window.hpp"
#include "../utils/game-stats.hpp"
#include "../utils/customer.hpp"
#include "./window.hpp"
#include "./ncurses-util.hpp"

/**
 * @brief Interface gráfica do HUD principal do jogo.
 */
class MainHUD : public BorderedWindow {
   private:
    void drawProgressBar();      //Desenha a barra de progresso
    void drawScore();            //Escreve a std::string da pontuação atual
    void drawDemand();           //Escreve clientes por segundo que entram na loja
    void drawStaticComponents(); //Desenha a parte estática do componente

    //Desenha parte dinâmica do componente
    void draw();


   public:
    /**
         * @brief Construtor da classe MainHUD. A pontuação é inicializada em 0.
         * @param target o alvo de pontuação que deve ser atingido para vencer
         */
    MainHUD();

};