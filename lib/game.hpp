#pragma once

#include <ncurses.h>

#include <string>

#include "./gui/game-GUI.hpp"

class Game {
   private:
    GameGUI* gui;
    int target;
    void finish();

   public:
    Game();
    ~Game();
    void run();
    void resize();
};