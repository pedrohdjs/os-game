#pragma once
#include <ncurses.h>

#include <string>
#include <thread>

#include "./Window.hpp"

class BorderedWindow : public Window {
    protected:

        std::string title;
        WINDOW* container;

        void setup();

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

        /**
         * Destrutor da janela
         */
        ~BorderedWindow();

        /**
         * Desenha a janela.
         */
        void draw();

        /**
         * Faz o refresh da janela.
         */
        void refresh();
};