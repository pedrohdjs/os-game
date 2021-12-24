#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include "./game-stats.hpp"

class Customer {
	private:
		static int customerRate;	// Quantidade de clientes que entra na loja
		static int rateIncrease;	// Incremento do rate de clientes
		static int increaseTime; 	// Tempo para o rate de clientes aumentar
		static int customerTime; 	// Tempo entre os clientes novos aparecerem

	public:
		static int getCustomerRate();
		//static int getRateIncrease();
		//static int getIncreaseTime();
		static void increaseRate();
		static void customerIncrease();
};