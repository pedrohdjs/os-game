#include "./Window.hpp"
#include "./BorderedWindow.hpp"
#include "./constants.hpp"
#include "./ncurses_util.hpp"
#include <iostream>
#include <string>

using namespace std;

class MainHUD : public BorderedWindow {
    private:
        int target; //Pontuação necessária para vencer
        int score; //Pontuação atual
        void drawProgressBar(); //Desenha a barra de progresso
        void drawScore(); //Escreve a string da pontuação atual
        
    public:
        /**
         * @brief Construtor da classe MainHUD. A pontuação é inicializada em 0.
         * 
         * @param target o alvo que deve ser atingido para vencer
         */
        MainHUD(int target);

        //Desenha parte dinâmica do componente
        void draw();

        //Recarrega a pontuação
        void refresh();

        //Desenha componentes estáticos
        void setup();

        //Define a pontuação
        void setScore(int score);
};