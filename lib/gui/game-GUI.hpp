#pragma once
#include <ncurses.h>

#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../cooker/cooker.hpp"
#include "../customers/customers.hpp"
#include "../game-stats/game-stats.hpp"
#include "../oven/oven.hpp"
#include "./bordered-window.hpp"
#include "./main-HUD.hpp"

/**
 * @brief Representa e agrega todos os componentes visuais do jogo.
 */
class GameGUI {
   private:
    BorderedWindow* mainWindow;  //Janela principal
    MainHUD* mainHUD;            //HUD principal com informações de progresso

    /**
	 * @brief Loop responsável por fazer refresh dos elementos visuais
	 */
    void refreshLoop();

    /**
	 * @brief Tela que mostra o tamanho atual da janela e o requerido
	 */
    void terminalSizeScreen();

    /**
	 * @brief Espera uma entrada qualquer do usuário ignorando entradas anteriores
	 */
    void waitInput();

   public:
    /**
	 * Construtor da janela do programa
	 * @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
	 */
    GameGUI(int refreshRate);

    /**
     * @brief Libera a memória memória alocada
     */
    ~GameGUI();

    /**
     * @brief Inicializa rotina de desenhar na tela
     */
    void show();

    /**
	 * @brief Executa o setup de cada um dos elementos visuais
	 */
    void setup();

    /**
	 * @brief Executa o refresh de cada um dos elementos visuais
	 */
    void refresh();

    /**
	 * @brief Tela de fim de jogo
	 */
    void endGameScreen();

    /**
	 * @brief Tela de inicio de jogo
	 */
    void startGameScreen();

    /**
	 * @brief Entra num loop detectando o tamanho da tela e testando os requisitos minimos 
	 * 
	 */
    void detectMinimumTerminalSize();

    /**
	 * @brief Escuta inputs do teclado e repassa para os outros elementos do jogo
	 * 
	 */
    void keyboardHandler();
};