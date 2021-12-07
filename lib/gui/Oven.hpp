#include "./Window.hpp"
#include "./BorderedWindow.hpp"
#include "./constants.hpp"
#include <iostream>
#include <string>

using namespace std;

class Oven : public BorderedWindow {
    private:

        int id; //Identificador do forno
        int status; //Estado atual do forno
        float progress; //Progresso da fornada atual

        void drawInfo(); //Imprime informações do forno
        
    public:
        /**
         * @brief Construtor da classe Oven. O forno é inicializado como não comprado.
         * 
         * @param id Identificador do forno.
         */
        Oven(int id);

        //Desenha parte dinâmica do componente
        void draw();

        //Recarrega o forno
        void refresh();

        //Desenha a parte estática do forno
        void setup();

        //Define a pontuação
        void setStatus(int status);

        //Define o progresso da fornada atual
        void setProgress(float progress);
};