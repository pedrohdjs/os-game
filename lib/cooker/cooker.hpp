#pragma once

#include <string>
#include <thread>

#include "../gui/bordered-window.hpp"
#include "../gui/window.hpp"
#include "../utils/game-stats.hpp"

using namespace std;

/**
 * @brief Classe que representa a interface gráfica de um funcionário.
 */
class Cooker {
   private:
    int id;      //Identificador do funcionário. Varia de 1 a 4.
    int status;  //Estado atual do funcionário. Devem ser usadas as constantes em gui/constants.hpp.
    int skill;   //Nível de habilidade do funcionário.
    float progress = 0;

    //Desenha parte dinâmica do componente visual
   public:
    class GUI : public BorderedWindow {
       private:
        friend class Cooker;
        Cooker& cooker;

       public:
        GUI(Cooker& cooker, int id);
        void draw();
        void drawInfo();
        void onRefresh();
        void drawProgressBar();
        void setup();
    };

    class ENGINE {
       private:
        friend class Cooker;
        Cooker& cooker;

       public:
        ENGINE(Cooker& cooker) : cooker{cooker} {};
        void keyboardHandler(char key);
        void logic();
    };

    GUI interface;
    ENGINE engine;

   public:
    /**
         * @brief Construtor da classe Cooker. O funcionário é inicializado como não comprado, a não ser que tenha ID 1.
         * @param id Identificador do funcionário.
         */
    Cooker(int id);
    void start();
};