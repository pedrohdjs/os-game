#include "./Window.hpp"
#include "./BorderedWindow.hpp"
#include "./constants.hpp"
#include "./ncurses_util.hpp"
#include <iostream>
#include <string>

using namespace std;

class MainHUD : public BorderedWindow {
    private:
        int target;
        int score;
        void drawProgressBar();
        void drawScore();
        
    public:
        MainHUD(int target);
        void draw();
        void refresh();
        void setup();
        void setScore(int score);
};