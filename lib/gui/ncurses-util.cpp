#include "./ncurses-util.hpp"

void wprintwc(BorderedWindow* w, std::string s, int y, bool clearLine) {
    int width = getmaxx(w->window);
    int height = getmaxy(w->window);
    int stringSize = (int)s.size();
    int offset = (width - stringSize) / 2;

    if (clearLine) {
        wmove(w->window, y, 0);
        wclrtoeol(w->window);

        prefresh(w->window, 0, 0, w->startHeight, w->startWidth, height, width);
        doupdate();
    }

    mvwprintw(w->window, y, offset, s.c_str());
}

void wprintwc(WINDOW* w, std::string s, int y, bool clearLine) {
    int width = getmaxx(w);
    int height = getmaxy(w);
    int stringSize = (int)s.size();
    int offset = (width - stringSize) / 2;

    if (clearLine) {
        std::string clear(width - 2, 32);
        mvwprintw(w, y, 1, clear.c_str());

        wrefresh(w);
    }

    mvwprintw(w, y, offset, s.c_str());
    prefresh(w, 0, 0, height, width, height, width);
}
