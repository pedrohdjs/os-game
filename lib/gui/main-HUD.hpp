#pragma once

#include <string>

#include "./bordered-window.hpp"
#include "../utils/game-stats.hpp"
#include "./window.hpp"
#include "./ncurses-util.hpp"

/**
 * @brief Interface gráfica do HUD principal do jogo.
 */
class MainHUD : public BorderedWindow {
   private:
    void drawProgressBar();  //Desenha a barra de progresso
    void drawScore();        //Escreve a std::string da pontuação atual
    void drawStaticComponents(); //Desenha a parte estática do componente

    //Desenha parte dinâmica do componente
    void draw();

    //Desenha as bordas da janela
    void setup();

   public:
    /**
         * @brief Construtor da classe MainHUD. A pontuação é inicializada em 0.
         * @param target o alvo de pontuação que deve ser atingido para vencer
         */
    MainHUD();

    //Recarrega a janela.
    void refresh();

};