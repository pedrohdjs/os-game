#include "./bordered-window.hpp"

std::mutex BorderedWindow::drawerMutex;

BorderedWindow::BorderedWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : Window(height, width, 0, 0), title{title} {
    window = newpad(height, width);  //cria as bordas
    //setup();
}

BorderedWindow::BorderedWindow(std::string title, int height, int width, int startHeight, int startWidth, WINDOW* parentWindow)
    : Window(height, width, startHeight, startWidth), title{title} {
    window = subpad(parentWindow, height, width, startHeight, startWidth);  //cria as bordas
    //setup();
}

BorderedWindow::~BorderedWindow() {
    delwin(window);
}

void BorderedWindow::refresh() {
    std::lock_guard<std::mutex> lock(drawerMutex);
    draw();
    pnoutrefresh(window, 0, 0, startHeight, startWidth, height, width);
}

void BorderedWindow::setup() {
    std::lock_guard<std::mutex> lock(drawerMutex);
    box(window, ACS_VLINE, ACS_HLINE);  //desenha a caixa em volta da janela criada
    if (title != "") mvwprintw(window, 0, 2, ("|" + title + "|").c_str());
}

void BorderedWindow::draw() {
}

void BorderedWindow::clear() {
    werase(window);
}