#include "./ncurses_util.hpp"

void wprintwc(WINDOW* w, string s, int y){
    int width = getmaxx(w);
    int stringSize = (int)s.size();
    int offset = (width-stringSize)/2;
    mvwprintw(w,y,offset,s.c_str());
}

void wclearline(WINDOW* w, int y){
    int width = 300;
    wmove(w,y,0);
    for(int i = 0; i<width; i++){
        mvwprintw(w,y,i," ");
    }
}