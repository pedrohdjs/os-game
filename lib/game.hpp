#pragma once

#include <ncurses.h>

#include <string>

#include "./gui/game-GUI.hpp"

/**
 * @brief Classe que representa o jogo em si
 * 
 */
class Game {
   private:
    GameGUI* gui;

    /**
	 * @brief Entra em um loop esperando o encerramento de todas as threads
	 * 
	 */
    void finish();

    /**
	 * @brief Inicializa os elementos do jogo 
	 * 
	 */
    void start();

   public:
    /**
    * @brief Cria a um novo Jogo
    * 
    */
    Game();

    /**
	 * @brief Finaliza o jogo, libera a memória alocada e finaliza as threads
	 * 
	 */
    ~Game();

    /**
	 * @brief Inicializa o game loop
	 * 
	 */
    void run();
};