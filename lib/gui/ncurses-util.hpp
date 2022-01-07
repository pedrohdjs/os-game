#pragma once

#include <ncurses.h>
#include <iostream>
#include <string>
#include "bordered-window.hpp"
/*
    Imprime uma std::string no centro de uma janela
*/
void wprintwc(BorderedWindow* w, std::string s, int y, bool clearLine);
void wprintwc(WINDOW* w, std::string s, int y, bool clearLine);