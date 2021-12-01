#pragma once
#include <ncurses.h>

#include <string>
#include <thread>

/**
 * @brief Classe abstrata para criação de janelas.
 * 
 */
class Window {
    protected:
        WINDOW* window;

        /**
         * Configuração inicial da janela. Deve ser sobreescrita em janelas mais específicas.
         */
        virtual void setup() = 0;

    public:
        /**
         * Construtor da janela
         * @param height altura da janela
         * @param width largura da janela
         * @param startHeigh posição X onde a janela será desenhada
         * @param startWidth posição Y onde a janela será desenhada
         */
        Window(int height, int width, int startHeight, int startWidth);

        /**
         * Destrutor da janela
         */
        ~Window();

        /**
         * Indica como a janela deve ser desenhada. Deve ser sobreescrita em janelas mais específicas.
         */
        virtual void draw() = 0;

        /**
         * Faz o refresh da janela atualizando de acordo com o que está escrito no buffer.
         */
        void refresh();
};