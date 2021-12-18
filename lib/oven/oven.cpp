#include "./oven.hpp"

Oven::Oven(int id) : interface{*this, id}, engine{*this}, id{id}, capacity{10}, progress{0} {
    status = (id == 1) ? GameStats::AVAILABLE : GameStats::NOT_PURCHASED;
}

void Oven::start() {
    interface.start();
}

void Oven::ENGINE::setStatus(int status) {
    oven.status = status;
}

void Oven::ENGINE::keyboardHandler(char key) {
    char actionKeys[4] = {'1', '2', '3', '4'};
    if (key == actionKeys[oven.id - 1] || key == actionKeys[oven.id - 1] + 32) {
        switch (oven.status) {
            case 0:
                oven.status = 1;
                break;
        }
    }
}

void Oven::ENGINE::bake(int cookiesToBake) {
    oven.currBakingCookies = cookiesToBake;
    oven.status = GameStats::BUSY;
}

int Oven::ENGINE::canBake(int cookiesToBake) {
    return oven.capacity - cookiesToBake;
}