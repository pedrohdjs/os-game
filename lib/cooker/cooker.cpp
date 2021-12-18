#include "./cooker.hpp"

Cooker::Cooker(int id) : interface{*this, id}, engine{*this}, id{id}, skill{1} {
    status = (id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED;
}

void Cooker::start() {
    interface.start();
}


void Cooker::ENGINE::logic() {
    cooker.progress += (cooker.progress > 1.05) ? -cooker.progress : 0.05;
}

void Cooker::ENGINE::keyboardHandler(char key) {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};
    if (key == actionKeys[cooker.id - 1] || key == actionKeys[cooker.id - 1] + 32) {
        switch (cooker.status) {
            case 0:
                cooker.status = 1;
                break;
            default:
                cooker.skill++;
                break;
        }
    }
}
