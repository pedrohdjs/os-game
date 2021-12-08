#include "./Window.hpp"
#include "./BorderedWindow.hpp"
#include "./constants.hpp"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Interface gráfica do forno
 */
class OvenGUI : public BorderedWindow {
    private:

        int id; //Identificador do forno. Valor de 1 a 4.
        int status; //Estado atual do forno. Usar constantes em gui/constants.hpp
        float progress; //Progresso da fornada atual. Valor de 0 a 1.

        //Imprime informações do forno
        void drawInfo();

        //Imprime barra de progresso
        void drawProgressBar(); 
        
        //Imprime fumaça do forno com base no progresso
        void drawSmoke();
        
        //Desenha a parte estática do forno
        void setup();

        //Desenha parte dinâmica do componente
        void draw();
    public:
        /**
         * @brief Construtor da classe OvenGUI. O forno é inicializado como não comprado.
         * 
         * @param id Identificador do forno.
         */
        OvenGUI(int id);

        //Recarrega o forno
        void refresh();

        //Define o estado do forno
        void setStatus(int status);

        //Define o progresso da fornada atual
        void setProgress(float progress);
};