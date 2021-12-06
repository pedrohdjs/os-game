#include "./ncurses_util.hpp"

void wprintwc(WINDOW* w, string s, int y){
    flushinp();
    int width = getmaxx(w);
    int stringSize = (int)s.size();
    int offset = (width-stringSize)/2;
    mvwprintw(w,y,offset,s.c_str());
}

void wclearline(WINDOW* w, int y){
    wmove(w,y,0);
    wclrtoeol(w);
}