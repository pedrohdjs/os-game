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

        std::string title; //O título da janela
        WINDOW* window; 
        static std::mutex drawerMutex;
        //Desenha a parte estática da janela

        //Desenha a parte dinâmica da janela
        void draw();


    public:
        /**
         * Construtor da janela
         * @param title titulo da janela
         * @param height altura da janela
         * @param width largura da janela
         * @param startHeigh posição X onde a janela será desenhada
         * @param startWidth posição Y onde a janela será desenhada
         */
        BorderedWindow(std::string title, int height, int width, int startHeight, int startWidth);

        //Destrutor da janela
        ~BorderedWindow();

        //Faz o refresh da janela.
        void refresh();

        void setup();
        void clear();
};