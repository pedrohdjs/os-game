#include "./Window.hpp"

#include <iostream>

Window::Window(int height, int width, int startHeight, int startWidth){
    window = newwin(height, width, startHeight, startWidth);  //cria a janela
}

Window::~Window() {
    delwin(window);
}

void Window::refresh() {
    draw();
    wrefresh(window);
}
