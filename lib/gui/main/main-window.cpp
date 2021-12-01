#include "./main-window.hpp"

MainWindow::MainWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : BoxWindow::BoxWindow(title, height, width, startHeight, startWidth) {
    scrollok(window, true);  //adiciona um scroll na janela de mensagem
}

void MainWindow::draw() {
    
}
