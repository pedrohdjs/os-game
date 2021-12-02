#include "./Window.hpp"
#include "./constants.hpp"
#include <iostream>

using namespace std;

class ProgressBar : public Window {
    private:
        int target;
        int current;
        
    public:
        ProgressBar(int target);
        void draw();
        void refresh();
        void setup();
};