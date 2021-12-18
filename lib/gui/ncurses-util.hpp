#pragma once

#include <ncurses.h>
#include <iostream>
#include <string>

using namespace std;
/*
    Imprime uma string no centro de uma janela
*/
void wprintwc(WINDOW* w, string s, int y);

using namespace std;
/*
    Limpa uma linha de uma janela
*/
void wclearline(WINDOW* w, int y);