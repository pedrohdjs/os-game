#pragma once

#include <ncurses.h>
#include <iostream>
#include <string>

/*
    Imprime uma std::string no centro de uma janela
*/
void wprintwc(WINDOW* w, std::string s, int y);

/*
    Limpa uma linha de uma janela
*/
void wclearline(WINDOW* w, int y);