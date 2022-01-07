#include "game-stats.hpp"

int GameStats::numberOfCookies = 0;
int GameStats::totalNumberOfCustomers = 0;
int GameStats::totalNumberOfCookies = 0;
int GameStats::totalNumberOfCookiesUser = 0;
int GameStats::frameRate = 7;
int GameStats::frameRateDelay = 1000 / 7;
int GameStats::target = 1000;

int GameStats::CURRENT_HEIGHT = 0;
int GameStats::CURRENT_WIDTH = 0;

bool GameStats::running = false;
bool GameStats::victory = false;

std::atomic<int> GameStats::numberOfThreads(0);

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
    if (!GameStats::isRunning()) return false;

    if (cookiesToBeAdded > 0) totalNumberOfCookies += cookiesToBeAdded;
    if (cookiesToBeAdded + numberOfCookies >= 0) {
        numberOfCookies += cookiesToBeAdded;

        if (numberOfCookies >= target) {
            victory = true;
            end();
        }

        return true;
    }

    return false;
}

void GameStats::customerArrival(int numberOfCustomers) {
    std::lock_guard<std::mutex> lock(cookiesMutex);
    if (!GameStats::isRunning()) return;

    numberOfCookies -= 30*numberOfCustomers;

    if (numberOfCookies <= -1 * target) {
        victory = false;
        end();
    }
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

void GameStats::addThread() {
    numberOfThreads++;
}

void GameStats::removeThread() {
    numberOfThreads--;
}

int GameStats::getNumberOfThreads() {
    return numberOfThreads;
}

void GameStats::detectTerminalResize() {
    int newHeight, newWidth;
    getmaxyx(stdscr, newHeight, newWidth);
    if (newHeight != GameStats::CURRENT_HEIGHT || newWidth != GameStats::CURRENT_WIDTH) {
        clear();
        refresh();
		GameStats::CURRENT_HEIGHT = newHeight;
        GameStats::CURRENT_WIDTH = newWidth;
    }
}