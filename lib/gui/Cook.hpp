#include "./Window.hpp"
#include "./BorderedWindow.hpp"
#include "./constants.hpp"
#include <iostream>
#include <string>

using namespace std;

class Cook : public BorderedWindow {
    private:

        int id; //Identificador do funcionário
        int status; //Estado atual do funcionário
        int skill; //Nível de habilidade do funcionário

        void drawInfo(); //Imprime informações do funcionário
        
    public:
        /**
         * @brief Construtor da classe Cook. O funcionário é inicializado como não comprado, a não ser que tenha ID 1.
         * 
         * @param id Identificador do funcionário.
         */
        Cook(int id);

        //Desenha parte dinâmica do componente
        void draw();

        //Recarrega o funcionário
        void refresh();

        //Desenha a parte estática do funcionário
        void setup();

        //Define a pontuação
        void setStatus(int status);

        //Define o progresso da fornada atual
        void setSkill(int skill);
};