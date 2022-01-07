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
        WINDOW* window; //Janela com o conteúdo da janela
        /**
         * Configuração inicial da janela, com desenho de partes estáticas.
         * Deve ser sobreescrita em janelas mais específicas.
         */
        virtual void setup() = 0;

        //Desenho de partes dinâmicas da janela
        virtual void draw() = 0;


    public:
        /**
         * Construtor da janela
         * @param height altura da janela
         * @param width largura da janela
         * @param startHeigh posição X onde a janela será desenhada
         * @param startWidth posição Y onde a janela será desenhada
         */
        Window(int height, int width, int startHeight, int startWidth);
        
		int width; //Largura da janela
        int height; //Altura da janela
        int startWidth;
        int startHeight;

        //Destrutor da janela
        ~Window();

        //Faz o refresh da janela atualizando de acordo com o que está escrito no buffer.
        void refresh();

        //Retorna a janela do ncurses 
        WINDOW* getWindow();
};