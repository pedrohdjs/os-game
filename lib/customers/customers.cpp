#include "./customers.hpp"

int Customers::customersRate = 1;
int Customers::rateIncrease = 1;
int Customers::increaseTime = 1000;
int Customers::customersTime = 10000;
std::mutex Customers::customerMutex;

void Customers::customersIncrease() {
    std::thread customersCounter([]() {
        int tickCounter = 0;
        while (GameStats::isRunning()) {
            if (tickCounter * 100 >= customersTime) {
                customerMutex.lock();
                Customers::customersRate += rateIncrease;
                customerMutex.unlock();
                tickCounter = 0;
            }
            tickCounter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        GameStats::removeThread();
    });
    customersCounter.detach();
    GameStats::addThread();
}

void Customers::increaseRate() {
    std::thread customersRateThread([]() {
        int tickCounter = 0;
        while (GameStats::isRunning()) {
            if (tickCounter * 100 >= increaseTime) {
                customerMutex.lock();
                GameStats::customerArrival(Customers::customersRate);
                GameStats::totalNumberOfCustomers += Customers::customersRate;
                customerMutex.unlock();
                tickCounter = 0;
            }
            tickCounter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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