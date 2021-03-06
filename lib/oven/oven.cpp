#include "./oven.hpp"

Oven::Oven(int id, WINDOW* parentWindow) : interface{*this, id, parentWindow}, engine{*this}, id{id}, capacity{10}, progress{0} {
    setStatus((id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED);
}

void Oven::start() {
    std::thread customerRateThread([&]() {
        while (GameStats::isRunning()) {
            engine.logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        GameStats::removeThread();
    });

    customerRateThread.detach();
    GameStats::addThread();
}

void Oven::setStatus(int newStatus) {
    status = newStatus;
}

int Oven::ENGINE::getStatus() {
    return oven.status;
}

int Oven::ENGINE::getCapacity() {
    return oven.capacity;
}

int Oven::ENGINE::getMaxCapacity() {
    int max = GameStats::Ovens[0]->engine.getCapacity();
    //percorre todos os fornos
    for (auto oven : GameStats::Ovens) {
        if (oven->engine.getStatus() && (max <= oven->engine.getCapacity())) {
            max = oven->engine.getCapacity();
        }
    }

    return max;
}

void Oven::ENGINE::keyboardHandler(char key) {
    char actionKeys[4] = {'1', '2', '3', '4'};

    if (key == actionKeys[oven.id - 1]) {
        switch (oven.status) {
            case GameStats::NOT_PURCHASED:

                if (GameStats::updateNumberOfCookies((oven.id - 1) * -10)) {
                    oven.setStatus(GameStats::AVAILABLE);
                }

                break;
            default:

                if (GameStats::updateNumberOfCookies(-10)) {
                    oven.capacity += 5;
                }

                break;
        }
    }
}

void Oven::ENGINE::bake(int cookiesToBake) {
    oven.currBakingCookies = cookiesToBake;
    oven.setStatus(GameStats::BUSY);
}

int Oven::ENGINE::canBake(int cookiesToBake) {
    return (oven.status == GameStats::AVAILABLE) ? oven.capacity - cookiesToBake : -1;
}

void Oven::ENGINE::logic() {
    if (oven.status == GameStats::BUSY) {
        oven.progress += 0.01;
        if (oven.progress >= 1.0) {
            GameStats::updateNumberOfCookies(oven.currBakingCookies);
            oven.progress = 0;
            oven.currBakingCookies = 0;
            oven.setStatus(GameStats::AVAILABLE);
        }
    }
}