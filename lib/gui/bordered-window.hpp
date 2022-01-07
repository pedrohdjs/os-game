#pragma once
#include <ncurses.h>
#include <mutex>
#include <string>
#include <thread>

#include "../game-stats/game-stats.hpp"
#include "./window.hpp"

/**
 * @brief Uma janela com borda
 */
class BorderedWindow : public Window {
    protected:

		/**
		 * @brief Mutex responsável por permitir que apenas 1 elemento seja desenhado por vez
		 */
        static std::mutex drawerMutex;

        /**
         * @brief desenha a parte dinâmica da janela
         */
        void draw();


    public:
        WINDOW* window; 
        /**
         * Construtor da janela principal
         * @param title titulo da janela
         * @param height altura da janela
         * @param width largura da janela
         * @param startHeigh posição X onde a janela será desenhada
         * @param startWidth posição Y onde a janela será desenhada
         */
        BorderedWindow(std::string title, int height, int width, int startHeight, int startWidth);
        
		/**
         * Construtor da janela secundária
         * @param title titulo da janela
         * @param height altura da janela
         * @param width largura da janela
         * @param startHeigh posição X onde a janela será desenhada
         * @param startWidth posição Y onde a janela será desenhada
		 * @param parentWindow janela pai
         */
        BorderedWindow(std::string title, int height, int width, int startHeight, int startWidth, WINDOW* parentWindow);

        std::string title;

        /**
         * @brief Libera a memória da janela
         */
        ~BorderedWindow();

        /**
         * @brief Atualiza a parte dinâmica do desenho da janela no buffer
         */
        void refresh();

        /**
         * @brief Atualiza a parte estática do desenho da janela no buffer
         */
        void setup();

		/**
		 * @brief limpa o buffer da janela 
		 */
        void clear();
};