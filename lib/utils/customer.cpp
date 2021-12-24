#include "./customer.hpp"

int Customer::customerRate = 1;
int Customer::rateIncrease = 6;
int Customer::increaseTime = 900;
int Customer::customerTime = 100;

int Customer::getCustomerRate(){
	return customerRate;
}

/*int Customer::getRateIncrease(){
	return rateIncrease;
}

int Customer::getIncreaseTime(){
	return increaseTime;
}*/

void Customer::increaseRate(){
    while (GameStats::isRunning()) {
    	customerRate += rateIncrease;

        std::this_thread::sleep_for(std::chrono::milliseconds(increaseTime));
    }
}

void Customer::customerIncrease(){
    while (GameStats::isRunning()) {
        GameStats::customerArrival(customerRate);

        
        std::this_thread::sleep_for(std::chrono::milliseconds(customerTime));
    }
}