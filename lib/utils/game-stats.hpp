#pragma once
#include <mutex>
#include <vector>

class GameStats {
   private:
    static int numberOfCookies;
    static int frameRate;
    static int frameRateDelay;
    static bool running;
    static int target;
    static std::mutex cookiesMutex;

   public:
    // constantes do jogo
    static const int WINDOW_WIDTH = 150;
    static const int WINDOW_HEIGHT = 40;

    static const int NOT_PURCHASED = 0;
    static const int AVAILABLE = 1;
    static const int BUSY = 2;


    static std::vector<class Oven*> Ovens;
    static std::vector<class Cooker*> Cooks;


   public:
    static void setFrameRate(int newFrameRate);
    static int getFrameRate();
    static int getFrameRateDelay();

    static int getNumberOfCookies();
    static bool updateNumberOfCookies(int cookiesToBeAdded);

    static void start();
    static bool isRunning();
    static void end();
};