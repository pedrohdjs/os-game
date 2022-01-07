#pragma once

#include <string>

#include "../game-stats/game-stats.hpp"
#include "../gui/bordered-window.hpp"
#include "../gui/window.hpp"

/**
 * @brief Interface gráfica do forno
 */
class Oven {
   private:
    int id;                 //Identificador do forno. Valor de 1 a 4.
    int status;             //Estado atual do forno. Usar constantes do GameStats
    float progress;         //Progresso da fornada atual. Valor de 0 a 1.
    int capacity = 10;      //Capacidade do forno
    int currBakingCookies;  //Quantidade de cookies que está assando

   public:
    /**
     * @brief Classe resoponsável pela parte gráfica do forno
     */
    class GUI : public BorderedWindow {
       private:
        friend class Oven;
        Oven& oven;  //Referência do forno

       public:
        /**
	     * @brief Cria uma nova interface de forno
	     * @param oven Forno concreto
	     * @param id Id do forno atual
	     * @param parentWindow Janela pai
	     */
        GUI(Oven& oven, int id, WINDOW* parentWindow);

        /**
		 * @brief Desenha o forno
		 */
        void draw();

        /**
		 * @brief Desenha o corpo do forno
		 */
        void body();

        /**
		 * @brief Imprime as informações do forno
		 */
        void drawInfo();

        /**
		 * @brief Desenha a fumaça do forno
		 */
        void drawSmoke();

        /**
		 * @brief Desenha a barra de progresso
		 */
        void drawProgressBar();
    };

    /**
	 * @brief Classe responsável pela lógica do forno
	 */
    class ENGINE {
       private:
        friend class Oven;
        Oven& oven;  //Referência do forno

       public:
        /**
	     * @brief Cria uma nova engine de forno
	     * @param oven Forno concreto
	     */
        ENGINE(Oven& oven) : oven{oven} {};

        /**
		 * @brief Recebe as entradas do teclado
		 * @param key tecla recebida
		 */
        void keyboardHandler(char key);

        /**
		 * @brief Lógica de funcionamento forno
		 */
        void logic();

        /**
		 * @brief Retorna o status atual do forno
		 * @return status atual do forno
		 */
        int getStatus();

        /**
		 * @brief Retorna a capacidade atual do forno
		 * @return capacidade atual do forno 
		 */
        int getCapacity();

        /**
		 * @brief Retorna a capacidade do maior dos fornos
		 * @return Capacidade do maior dos fornos
		 */
        static int getMaxCapacity();

        /**
		 * @brief Seta o status como ocupado e atualiza a quantidade de biscoitos atual do forno
		 * @param cookiesToBake cookies que serão assados
		 */
        void bake(int cookiesToBake);

        /**
		 * @brief Testa se é possível assar uma certa quantidade de biscoitos
		 * @param cookiesToBake Quantiadade de biscoitos que se deseja assar
		 * @return -1 caso não seja possivel e a capacidade do forno caso seja
		 */
        int canBake(int cookiesToBake);
    };

    /**
	 * @brief Atualiza o estado do forno
	 * @param status novo estado
	 */
    void setStatus(int status);
    GUI interface;
    ENGINE engine;

   public:
    /**
	 * @brief Construtor da classe OvenGUI. O forno é inicializado como não comprado.
	 * 
	 * @param id Identificador do forno.
	 * @param parentWindow janela pai
	 */
    Oven(int id, WINDOW* parentWindow);

    /**
	 * @brief Inicializa loop da lógica do forno
	 */
    void start();
};