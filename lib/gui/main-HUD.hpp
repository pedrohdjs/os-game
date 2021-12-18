#pragma once

#include <string>

#include "./bordered-window.hpp"
#include "../utils/game-stats.hpp"
#include "./window.hpp"
#include "./ncurses-util.hpp"

using namespace std;

/**
 * @brief Interface gráfica do HUD principal do jogo.
 */
class MainHUD : public BorderedWindow {
   private:
    int target;              //Pontuação necessária para vencer
    int score;               //Pontuação atual
    void drawProgressBar();  //Desenha a barra de progresso
    void drawScore();        //Escreve a string da pontuação atual

    //Desenha parte dinâmica do componente
    void draw();

    //Desenha componentes estáticos
    void setup();

   public:
    /**
         * @brief Construtor da classe MainHUD. A pontuação é inicializada em 0.
         * @param target o alvo de pontuação que deve ser atingido para vencer
         */
    MainHUD(int target);

    //Recarrega a janela.
    void refresh();

    //Atualiza a pontuação.
    void setScore(int score);
};