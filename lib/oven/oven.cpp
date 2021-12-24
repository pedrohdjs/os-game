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
        switch(oven.status){
            case GameStats::NOT_PURCHASED:
                if(GameStats::updateNumberOfCookies((oven.id - 1)* -10)){
                    oven.status = GameStats::AVAILABLE;
                }
                break;
            default:
                if(GameStats::updateNumberOfCookies(-10)){
                    oven.capacity += 5;
                }
                break;

        }
        if((oven.status == GameStats::NOT_PURCHASED) && (GameStats::updateNumberOfCookies((oven.id - 1)* -10))) {
        }
    }
}

void Oven::ENGINE::bake(int cookiesToBake) {
    oven.currBakingCookies = cookiesToBake;
    oven.status = GameStats::BUSY;
}

int Oven::ENGINE::canBake(int cookiesToBake) {
    return (oven.status == GameStats::AVAILABLE) ? oven.capacity - cookiesToBake : -1;
}

void Oven::ENGINE::logic() {
    if (oven.status == GameStats::BUSY) {
        oven.progress += 0.01;
        if (oven.progress > 1.02) {
            GameStats::updateNumberOfCookies(oven.currBakingCookies);
            oven.progress = 0;
            oven.currBakingCookies = 0;
            oven.status = GameStats::AVAILABLE;
        }
    }
}