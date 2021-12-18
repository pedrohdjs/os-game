#pragma once

#include <string>

#include "../gui/bordered-window.hpp"
#include "../gui/window.hpp"
#include "../utils/game-stats.hpp"

/**
 * @brief Interface gráfica do forno
 */
class Oven {
   private:
    int id;          //Identificador do forno. Valor de 1 a 4.
    int status;      //Estado atual do forno. Usar constantes em gui/constants.hpp
    float progress;  //Progresso da fornada atual. Valor de 0 a 1.
    int capacity = 10;
    int currBakingCookies;

   public:
    class GUI : public BorderedWindow {
       private:
        friend class Oven;
        Oven& oven;

       public:
        GUI(Oven& oven, int id);
        void draw();
        void drawInfo();
        void onRefresh();
        void drawSmoke();
        void drawProgressBar();
        void setup();
    };

    class ENGINE {
       private:
        friend class Oven;
        Oven& oven;

       public:
        ENGINE(Oven& oven) : oven{oven} {};
        void keyboardHandler(char key);
        void logic();
        void setStatus(int status);
        int getStatus();
        void bake(int cookiesToBake);
        int canBake(int cookiesToBake);
    };

    GUI interface;
    ENGINE engine;

   public:
    /**
         * @brief Construtor da classe OvenGUI. O forno é inicializado como não comprado.
         * 
         * @param id Identificador do forno.
         */
    Oven(int id);
    void start();
};