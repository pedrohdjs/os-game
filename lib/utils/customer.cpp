#include "./customer.hpp"

int Customer::customerRate = 8;
int Customer::rateIncrease = 8;
int Customer::increaseTime = 15000;
int Customer::customerTime = 1000;

int Customer::getCustomerRate() {
    return customerRate;
}

void Customer::start() {
    increaseRate();
    customerIncrease();
}

void Customer::increaseRate() {

    std::thread customerRateThread([&]() {
        while (GameStats::isRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(increaseTime));
            customerRate += rateIncrease;
        }
        GameStats::removeThread();
    });
	
    customerRateThread.detach();
    GameStats::addThread();
}

void Customer::customerIncrease() {

    std::thread customerCounter([]() {
        while (GameStats::isRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(customerTime));
            GameStats::customerArrival(customerRate);
        }
        GameStats::removeThread();
    });

    customerCounter.detach();
    GameStats::addThread();
}