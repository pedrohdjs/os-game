#include "./window.hpp"

Window::Window(int height, int width, int startHeight, int startWidth) : width{width},
                                                                         height{height} {
    window = newwin(height, width, startHeight, startWidth);  //cria a janela
}

Window::~Window() {
    delwin(window);
}

void Window::refresh() {
    draw();
    wrefresh(window);
}

WINDOW* Window::getWindow() {
    return window;
}