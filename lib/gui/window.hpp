#pragma once

#include <ncurses.h>

#include <string>
#include <thread>

/**
 * @brief Classe abstrata para criação de janelas.
 */
class Window {
   protected:
    WINDOW* window;  //Janela com o conteúdo da janela
    /**
	 * Configuração inicial da janela, com desenho de partes estáticas.
	 * Deve ser sobreescrita em janelas mais específicas.
	 */

    //Desenha de partes estaticas da janela
    virtual void setup() = 0;

    //Desenha de partes dinâmicas da janela
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

    int width;        //Largura da janela
    int height;       //Altura da janela
    int startWidth;   //Posição x onde a janela será desenhada
    int startHeight;  // Posição y onde a janela será desenhada

    /**
	 * @brief libera a memória alocada 
	 */
    ~Window();

    /**
	 * @brief Redesenha a janela e faz o update do buffer
	 * 
	 */
    void refresh();

    /**
	 * @brief Retorna a janela do ncurses 
	 * 
	 * @return ponteiro para a janela
	 */
    WINDOW* getWindow();
};