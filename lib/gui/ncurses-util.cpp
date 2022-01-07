#include "./ncurses-util.hpp"

void wprintwc(BorderedWindow* w, std::string s, int y, bool clearLine) {
    //flushinp();

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

    std::string message(offset - 1, 32);
    message += s;

    for (int i = 0; i < message.size(); i++) {
        message[i] = (message[i] == ' ') ? ' ' : message[i];
    }

    mvwprintw(w->window, y, 1, message.c_str());
}

void wprintwc(WINDOW* w, std::string s, int y, bool clearLine) {
    //flushinp();

    int width = getmaxx(w);
    int height = getmaxy(w);
    int stringSize = (int)s.size();
    int offset = (width - stringSize) / 2;

    if (clearLine) {
        std::string clear(width - 2, 32);
        mvwprintw(w, y, 1, clear.c_str());
        wrefresh(w);
    }

    std::string message(offset - 1, 32);
    message += s;

    for (int i = 0; i < message.size(); i++) {
        message[i] = (message[i] == ' ') ? 32 : message[i];
    }

    mvwprintw(w, y, 1, message.c_str());
    prefresh(w, 0, 0, height, width, height, width);
}
