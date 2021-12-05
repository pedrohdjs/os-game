#pragma once

#include <ncurses.h>

#include <iostream>
#include <string>

#include "./gui/GameGUI.hpp"


using namespace std;

class Game {
    private:
        GameGUI *gui;
        int target;

    public:
        Game();
        void run();
};