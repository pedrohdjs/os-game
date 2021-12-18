#include <iostream>
#include <string>
#include <thread>

#include "./BorderedWindow.hpp"
#include "./GameStats.hpp"
#include "./Window.hpp"
#include "./GameStats.hpp"
#include "GameStats.hpp"

using namespace std;

/**
 * @brief Classe que representa a interface gráfica de um funcionário.
 */
class CookGUI : public BorderedWindow {
   private:
    int id;      //Identificador do funcionário. Varia de 1 a 4.
    int status;  //Estado atual do funcionário. Devem ser usadas as constantes em gui/constants.hpp.
    int skill;   //Nível de habilidade do funcionário.
    float progress = 0;

    //Desenha parte dinâmica do componente visual
    void drawLoop();
    void draw();

    //Imprime informações do componente visual
    void drawInfo();

    //Desenha a parte estática do componente visual
    void setup();

    //Imprime barra de progresso
    void drawProgressBar();

   public:
    /**
         * @brief Construtor da classe CookGUI. O funcionário é inicializado como não comprado, a não ser que tenha ID 1.
         * @param id Identificador do funcionário.
         */
    CookGUI(int id);

    //Recarrega o funcionário

    //Define o status. Usar as contantes em gui/constants.hpp
    void setStatus(int status);

    //Define o progresso da fornada atual
    void setSkill(int skill);

    void setProgress(float progress);

    void onRefresh();

    void keyboardHandler(char key);
};