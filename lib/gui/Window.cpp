#include "./Window.hpp"

#include <iostream>

Window::Window(int height, int width, int startHeight, int startWidth){
    window = newwin(height, width, startHeight, startWidth);  //cria a janela
    this->width = width;
    this->height = height;
}

Window::~Window() {
    delwin(window);
}

void Window::refresh() {
    draw();
    wrefresh(window);
}

WINDOW* Window::getWindow(){
    return this->window;
}