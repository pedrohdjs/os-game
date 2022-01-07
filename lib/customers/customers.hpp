#pragma once

#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../game-stats/game-stats.hpp"

class Customers {
   private:
    static int rateIncrease;   // Incremento do rate de clientes
    static int increaseTime;   // Tempo para o rate de clientes aumentar
    static int customersTime;  // Tempo entre os clientes novos aparecerem
    static int customersRate;  // Tempo entre os clientes novos aparecerem

    static std::mutex customerMutex;  // Mutex responsável por impedir alterações/leituras simultâneas dos clientes

   public:
    /**
     * @brief Inicializa a chegada de clientes e o aumento de números de clientes por loop
     */
    static void start();

	/**
	 * @brief Aumenta a quantiadade de clientes
	 */
    static void increaseRate();

	/**
	 * @brief Aumenta a quantidade clientes que chegam por vez
	 */
    static void customersIncrease();

	/**
	 * @brief retorna o número de clientes que chega por segundo
	 * @return int número de clientes por segundo
	 */
    static int getCustomersRate();
};