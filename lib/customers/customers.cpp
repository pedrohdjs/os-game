#include "./customers.hpp"

int Customers::customersRate = 0;
int Customers::rateIncrease = 2;
int Customers::increaseTime = 1000;
int Customers::customersTime = 1000;
std::mutex Customers::customerMutex;

void Customers::customersIncrease() {
    std::thread customersCounter([]() {
        while (GameStats::isRunning()) {
            customerMutex.lock();
            Customers::customersRate += rateIncrease;
            customerMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(customersTime));
        }
        GameStats::removeThread();
    });
    customersCounter.detach();
    GameStats::addThread();
}

void Customers::increaseRate() {
    std::thread customersRateThread([]() {
        while (GameStats::isRunning()) {
            customerMutex.lock();
            GameStats::customerArrival(Customers::customersRate);
            customerMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(increaseTime));
        }
        GameStats::removeThread();
    });
    customersRateThread.detach();
    GameStats::addThread();
}

void Customers::start() {
    increaseRate();
    customersIncrease();
}