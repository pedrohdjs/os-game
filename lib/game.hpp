#pragma once

#include <ncurses.h>

#include <string>

#include "./gui/game-GUI.hpp"


using namespace std;

class Game {
    private:
        GameGUI gui;
        int target;

    public:
        Game();
        void run();
};