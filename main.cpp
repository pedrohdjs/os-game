#include <ncurses.h>
#include <chrono>
#include <thread>

#include "./lib/game.hpp"

using namespace std;

int main(int argc, char** argv) {
    initscr();


    WINDOW *win = newwin(10,60,0,0);
    refresh();

    box(win,0,0);
    wmove(win,1,1);
    wprintw(win,"This is my box");
    wrefresh(win);

    getch();

    endwin();
    return 0;
}