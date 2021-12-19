#include "./ncurses-util.hpp"

void wprintwc(WINDOW* w, std::string s, int y, bool clearLine){
    flushinp();

    if(clearLine){
        wmove(w,y,0);
        wclrtoeol(w);
        wrefresh(w);
    }
    
    int width = getmaxx(w);
    int stringSize = (int)s.size();
    int offset = (width-stringSize)/2;
    mvwprintw(w,y,offset,s.c_str());
}
