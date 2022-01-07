#pragma once
#include <mutex>
#include <vector>
#include <atomic>
#include <thread>
#include <ncurses.h>

class GameStats {
   private:
    static int numberOfCookies;
    static int frameRate;
    static int frameRateDelay;
    static bool running;
    static std::mutex cookiesMutex;
    static std::atomic<int> numberOfThreads;

   public:
    // constantes do jogo
    static const int WINDOW_WIDTH = 150;
    static const int WINDOW_HEIGHT = 40;

    static const int NOT_PURCHASED = 0;
    static const int AVAILABLE = 1;
    static const int BUSY = 2;
    static const int WAITING = 3;
    static const int RESTING  = 4;
    
	static int CURRENT_HEIGHT;
    static int CURRENT_WIDTH;

    static int target;
	
    static bool victory;
    static int totalNumberOfCookies;
    static int totalNumberOfCookiesUser;
    static int totalNumberOfCustomers;


    static std::vector<class Oven*> Ovens;
    static std::vector<class Cooker*> Cooks;


   public:
    static void setFrameRate(int newFrameRate);
    static int getFrameRate();
    static int getFrameRateDelay();
    
    static int getNumberOfCookies();
    static bool updateNumberOfCookies(int cookiesToBeAdded);
    static void customerArrival(int numberOfCustomers);

    static void start();
    static bool isRunning();
    static void end();
    static void addThread();
    static void removeThread();
	static int getNumberOfThreads();
    static void detectTerminalResize();
};