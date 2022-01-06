#include "./cooker.hpp"

std::mutex Cooker::goingToBake;

Cooker::Cooker(int id) : interface{*this, id}, engine{*this}, id{id}, skill{5} {
    setStatus((id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED);
}

void Cooker::setStatus(int newStatus){
    status = newStatus;
    interface.clear();
}

void Cooker::start() {

    std::thread cookerLogic([&]() {
        while (GameStats::isRunning()) {
            engine.logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    	GameStats::removeThread();
    });

    cookerLogic.detach();
    GameStats::addThread();
}

void Cooker::ENGINE::logic() {
    switch (cooker.status) {
        case GameStats::BUSY:
            cooker.progress += 0.02f;
            if (cooker.progress > 1.02f) {
                cooker.setStatus( GameStats::WAITING);
                findBestFitOven();
            }
            break;
        case GameStats::WAITING:
            findBestFitOven();
            break;

        case GameStats::AVAILABLE:
            cooker.setStatus(GameStats::BUSY);
            break;
        case GameStats::RESTING:
            cooker.progress += 0.05f;
            if (cooker.progress > 1.1f) {
                cooker.setStatus(GameStats::AVAILABLE);
                cooker.progress = 0;
            }
            break;
        default:
            break;
    }
}

void Cooker::ENGINE::findBestFitOven() {
    std::lock_guard<std::mutex> lock(cooker.goingToBake);
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
        cooker.setStatus(GameStats::RESTING);
        cooker.progress = 0;
    } 
}

void Cooker::ENGINE::keyboardHandler(char key) {
    char actionKeys[4] = {'Q', 'W', 'E', 'R'};
    if (key == actionKeys[cooker.id - 1] || key == actionKeys[cooker.id - 1] + 32) {
        switch (cooker.status) {
            case GameStats::NOT_PURCHASED:
                if (GameStats::updateNumberOfCookies((cooker.id) * -5)) {
                    cooker.setStatus(GameStats::AVAILABLE);
                }
                break;
            default:
                if (cooker.skill < (GameStats::Ovens[0]->engine.getMaxCapacity())) {
                    if (GameStats::updateNumberOfCookies((cooker.skill + 1) * -3)) {
                        cooker.skill++;
                    }
                }
                break;
        }
    }
}
