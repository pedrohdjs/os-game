#pragma once

#include <mutex>
#include <string>
#include <thread>

#include "../game-stats/game-stats.hpp"
#include "../gui/bordered-window.hpp"
#include "../gui/window.hpp"
#include "../oven/oven.hpp"

/**
 * @brief Classe que representa a interface gráfica de um funcionário.
 */
class Cooker {
   private:
    int id;                         //Identificador do funcionário. Varia de 1 a 4.
    int status;                     //Estado atual do funcionário. Devem ser usadas as constantes em gui/constants.hpp.
    int skill;                      //Nível de habilidade do funcionário.
    float progress = 0;             //Progresso atual do cozinheiro
    static std::mutex goingToBake;  // Mutex responsável por deixar apenas um cozinheiro buscar o forno ideal por vez

   public:
    class GUI : public BorderedWindow {
       private:
        friend class Cooker;
        Cooker& cooker;  // Referência ao objeto concreto

       public:
        /**
	    * @brief Cria uma nova interface de cozinheiro
	    * 
	    * @param cooker Cozinheiro concreto
	    * @param id Id do cozinheiro
	    * @param parentWindow Janela Pai
	    */
        GUI(Cooker& cooker, int id, WINDOW* parentWindow);

        /**
		 * @brief Desenha o cozinheiro
		 */
        void draw();

        /**
		 * @brief Desenha o corpo da janela do cozinheiro
		 */
        void body();

        /**
		 * @brief Imprime as informações de compra e status
		 */
        void drawInfo();

        /**
		 * @brief Desenha a barra de progresso
		 */
        void drawProgressBar();

        /**
		 * @brief Imprime a mensagem de possivel upgrade ou não
		 */
        void drawUpgradeMessage();
    };

    class ENGINE {
       private:
        friend class Cooker;
        Cooker& cooker;

       public:
        ENGINE(Cooker& cooker) : cooker{cooker} {};

        /**
		 * @brief Recebe as entradas do teclado
		 * @param key tecla digitada
		 */
        void keyboardHandler(char key);

        /**
		 * @brief lógica de execução do cozinheiro
		 */
        void logic();

        /**
		 * @brief Encontra o forno que tem a capacidade que mais se adequa a quantiadade de cookies produzida
		 */
        void findBestFitOven();
    };

    /**
	 * @brief Atualiza o status do forno
	 * @param newStatus novo status
	 */
    void setStatus(int newStatus);
    GUI interface;
    ENGINE engine;

   public:
    /**
	 * @brief Construtor da classe Cooker. O funcionário é inicializado como não comprado, a não ser que tenha ID 1.
     * @param id Identificador do funcionário.
	 * @param parentWindow janela pai
     */
    Cooker(int id, WINDOW* parentWindow);

    /**
	 * @brief inicializa o loop de lógica do cozinheiro
	 */
    void start();
};