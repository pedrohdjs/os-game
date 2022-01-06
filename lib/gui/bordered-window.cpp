#include "./bordered-window.hpp"

std::mutex BorderedWindow::drawerMutex;

BorderedWindow::BorderedWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : Window(height, width, startHeight, startWidth), title{title} {

    container = newwin(height, width, startHeight, startWidth);               //cria as bordas
    window = newwin(height - 2, width - 2, startHeight + 1, startWidth + 1);  //cria a janela real
    setup();
}

BorderedWindow::~BorderedWindow() {
    delwin(window);
    delwin(container);
}

void BorderedWindow::refresh() {
    std::lock_guard<std::mutex> lock(drawerMutex);
    draw();
    setup();
    wrefresh(container);
    wrefresh(window);
}

void BorderedWindow::setup() {
    box(container, ACS_VLINE, ACS_HLINE);  //desenha a caixa em volta da janela criada
    if (title != "") mvwprintw(container, 0, 2, ("|" + title + "|").c_str());
}

void BorderedWindow::draw() {
}

WINDOW* BorderedWindow::getContainer() {
    return container;
}