#pragma once
#include <ncurses.h>

#include <string>
#include <thread>

#include "./Window.hpp"

using namespace std;


/**
 * @brief Uma janela com borda
 */
class BorderedWindow : public Window {
    protected:

        std::string title; //O título da janela
        WINDOW* container; //Janela com as bordas da janela

        //Desenha a parte estática da janela
        void setup();

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

        //Retorna a janela com as bordas da janela.
        WINDOW* getContainer();
};