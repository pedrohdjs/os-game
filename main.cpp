#include "./lib/game.hpp"

int main(int argc, char** argv) {
    initscr();
    Game g = Game();
    g.run();
    endwin();
    return 0;
}