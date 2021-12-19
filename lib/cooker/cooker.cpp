#include "./cooker.hpp"

Cooker::Cooker(int id) : interface{*this, id}, engine{*this}, id{id}, skill{5} {
    status = (id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED;
}

void Cooker::start() {
    interface.start();
}

void Cooker::ENGINE::logic() {
    switch (cooker.status) {
        case GameStats::BUSY:

            cooker.progress += 0.02f;
            if (cooker.progress > 1.02f) {
                findBestFitOven();
            }

            break;
        case GameStats::AVAILABLE:
            cooker.status = GameStats::BUSY;
            break;
        default:
            break;
    }
}

void Cooker::ENGINE::findBestFitOven() {
    int bestFitIdx = 0;
    int bestFitValue = GameStats::Ovens[0]->engine.canBake(cooker.skill);

    for (int i = 0; i < GameStats::Ovens.size(); i++) {
        int currValue = GameStats::Ovens[i]->engine.canBake(cooker.skill);
        if ((currValue > 0 && currValue < bestFitValue) || bestFitValue < 0) {
            bestFitIdx = i;
            bestFitValue = currValue;
        }
    }

    if (bestFitValue >= 0) {
        GameStats::Ovens[bestFitIdx]->engine.bake(cooker.skill);
        cooker.status = GameStats::AVAILABLE;
        cooker.progress = 0;
    } else {
        //exit(0);
    }
}

void Cooker::ENGINE::keyboardHandler(char key) {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};
    if (key == actionKeys[cooker.id - 1] || key == actionKeys[cooker.id - 1] + 32) {
        switch (cooker.status) {
            case 0:
                cooker.status = GameStats::AVAILABLE;
                break;
            default:
                cooker.skill++;
                break;
        }
    }
}
