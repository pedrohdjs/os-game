#include "./Window.hpp"
#include "./BorderedWindow.hpp"
#include "./constants.hpp"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Classe que representa a interface gráfica de um funcionário.
 */
class CookGUI : public BorderedWindow {
    private:

        int id; //Identificador do funcionário. Varia de 1 a 4.
        int status; //Estado atual do funcionário. Devem ser usadas as constantes em gui/constants.hpp.
        int skill; //Nível de habilidade do funcionário.
        
        //Desenha parte dinâmica do componente visual
        void draw();

        //Imprime informações do componente visual
        void drawInfo(); 

        //Desenha a parte estática do componente visual
        void setup();

    public:
        /**
         * @brief Construtor da classe CookGUI. O funcionário é inicializado como não comprado, a não ser que tenha ID 1.
         * @param id Identificador do funcionário.
         */
        CookGUI(int id);

        //Recarrega o funcionário
        void refresh();

        //Define o status. Usar as contantes em gui/constants.hpp
        void setStatus(int status);

        //Define o progresso da fornada atual
        void setSkill(int skill);
};