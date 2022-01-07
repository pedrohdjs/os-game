#pragma once

#include <ncurses.h>

#include <iostream>
#include <string>

#include "bordered-window.hpp"

/**
 * @brief Imprime uma string no centro de uma janela do tipo pad
 * 
 * @param w janela onde a string vai ser impressa
 * @param s string a ser impressa
 * @param y altura da impressão
 * @param clearLine verdadeiro caso se deseje limpar a linha
 */
void wprintwc(BorderedWindow* w, std::string s, int y, bool clearLine);

/**
 * @brief Imprime uma string no centro de uma janela do tipo window
 * 
 * @param w janela onde a string vai ser impressa
 * @param s string a ser impressa
 * @param y altura da impressão
 * @param clearLine verdadeiro caso se deseje limpar a linha
 */
void wprintwc(WINDOW* w, std::string s, int y, bool clearLine);