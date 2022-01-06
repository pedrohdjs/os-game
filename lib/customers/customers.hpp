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
    static std::mutex customerMutex;

   public:
    static int customersRate;  // Tempo entre os clientes novos aparecerem
    static void start();
    static void increaseRate();
    static void customersIncrease();
};