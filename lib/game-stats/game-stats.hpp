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
    static const int WINDOW_WIDTH = 152;
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
	/**
	 * @brief Define o frame rate do programa
	 * @param newFrameRate novo frame rate
	 */
    static void setFrameRate(int newFrameRate);

	/**
	 * @brief Retorna o frame rate 
	 * @return frame rate
	 */
    static int getFrameRate();

	/**
	 * @brief Retorna o delay de acordo com o frame rate definido
	 * @return delay em ms
	 */
    static int getFrameRateDelay();

    /**
	 * @brief Retorna o número de cookies
	 * @return número de cookies
	 */
    static int getNumberOfCookies();

	/**
	 * @brief Tenta adicionar ou subtrair uma quantidade de cookies ao total sem deixar o resultado menor que 0
	 * 
	 * @param cookiesToBeAdded quantidade a ser adicionada
	 * @return verdadeiro se foi possivel e falso caso não seja
	 */
    static bool updateNumberOfCookies(int cookiesToBeAdded);


	/**
	 * @brief Subtrai uma quantidade do total de cookies
	 * 
	 * @param numberOfCustomers quantidade a ser subtraida
	 */
    static void customerArrival(int numberOfCustomers);

	/**
	 * @brief Define o status do jogo como running
	 * 
	 */
    static void start();

	/**
	 * @brief Retorna se o jogo está rodando ou não
	 * 
	 * @return estado atual do jogo
	 */
    static bool isRunning();

	/**
	 * @brief define o estado do jogo (running) como falso
	 */
    static void end();

	/**
	 * @brief Soma 1 no contador de threads
	 */
    static void addThread();

    /**
	 * @brief Subtrai 1 do contador de threads
	 */
    static void removeThread();

    /**
	 * @brief Retorna número de threads que está rodando
	 * @return número de threads
	 */
    static int getNumberOfThreads();

	/**
	 * @brief detecta se houve resize do terminal e atualiza as variáveis de tamanho da tela e, por fim, limpa a janela
	 */
    static void detectTerminalResize();
};