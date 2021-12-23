#include "game-stats.hpp"

int GameStats::numberOfCookies = 0;
int GameStats::frameRate = 7;
int GameStats::frameRateDelay = 1000 / 7;
bool GameStats::running = false;
int GameStats::target = 100;

std::vector<class Oven*> GameStats::Ovens;
std::vector<class Cooker*> GameStats::Cooks;

std::mutex GameStats::cookiesMutex;

void GameStats::setFrameRate(int newFrameRate) {
    frameRate = newFrameRate;
    frameRateDelay = 1000 / frameRate;
}

int GameStats::getFrameRate() {
    return frameRate;
}

int GameStats::getFrameRateDelay() {
    return frameRateDelay;
}

int GameStats::getNumberOfCookies() {
    return numberOfCookies;
}

bool GameStats::updateNumberOfCookies(int cookiesToBeAdded) {
    std::lock_guard<std::mutex> lock(cookiesMutex);
    if (cookiesToBeAdded + numberOfCookies >= 0) {
        numberOfCookies += cookiesToBeAdded;
        return true;
    }

    return false;
}

void GameStats::start() {
    running = true;
}

bool GameStats::isRunning() {
    return running;
}

void GameStats::end() {
    running = false;
}
