#include <ncurses.h>

#include "./lib/game.hpp"

using namespace std;

int main(int argc, char** argv) {
    initscr();
    printw("hello ncurses!");
    getchar();
    endwin();
    return 0;
}