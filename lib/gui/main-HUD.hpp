#pragma once

#include <sstream>
#include <string>

#include "../customers/customers.hpp"
#include "../game-stats/game-stats.hpp"
#include "./bordered-window.hpp"
#include "./ncurses-util.hpp"
#include "./window.hpp"

/**
 * @brief Interface gráfica do HUD principal do jogo.
 */
class MainHUD : public BorderedWindow {
   private:
    int maxProgressWidth;  //Tamanho máximo da barra de progresso;
    float currProgress;    // progresso atual da barra;

    /**
	 * @brief Desenha a barra de progresso
	 */
    void drawProgressBar();

    /**
	 * @brief Escreve a pontuação atual 
	 */
    void drawScore();

    /**
	 * @brief Imprime a quantidade de clientes por segundo que entram na loja 
	 */
    void drawDemand();

    /**
	 * @brief Desenha a parte estática do componente 
	 */
    void drawStaticComponents();

    /**
	 * @brief Apaga a antiga barra de progresso 
	 */
    void clearProgressBar();

    /**
	 * @brief Atualiza o progresso da barra 
	 */
    void updateCurrProgress();

    /**
	 * @brief Desenha o componente
	 */
    void draw();

   public:
    /**
	 * @brief Construtor da classe MainHUD. A pontuação é inicializada em 0.
	 * @param parentWindow janela pai
	 */
    MainHUD(WINDOW* parentWindow);
};