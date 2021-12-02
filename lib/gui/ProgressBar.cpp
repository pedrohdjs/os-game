#include "./ProgressBar.hpp"


ProgressBar::ProgressBar(int target) 
: Window(1,WINDOW_WIDTH/2,WINDOW_HEIGHT - 10,(WINDOW_WIDTH/2)/2) {
    this->target = target;
    this->current = -100;
    this->setup();
}

void ProgressBar::setup(){
    wmove(window,0,0);
    wprintw(window,"[");
    wmove(window,0,width/2);
    wprintw(window,"X");
    wmove(window,0,width-1);
    wprintw(window,"]");
    wmove(window,0,1);
}

void ProgressBar::refresh(){
    draw();
    wrefresh(window);
}

void ProgressBar::draw(){
    this->current++;
    int maxProgressWidth = (width - 3)/2;

    //Clear the progress bar
    wmove(window,0,1);
    for(int i = 0; i < maxProgressWidth; i++){
        wprintw(window," ");
    }
    wmove(window,0,width/2+1);
    for(int i = 0; i < maxProgressWidth; i++){
        wprintw(window," ");
    }

    float progress = (float)current/(float)target;
    cout << progress << endl;
    int progressWidth = abs((int)(progress * (float)maxProgressWidth));
    cout << progressWidth << endl;
    int start, end;
    if (progress > 0){
        start = width/2 + 1;
        end = start + progressWidth;
    }
    else {
        start = width/2 - progressWidth;
        end = width/2;
    }

    for(int i = start; i < end; i++){
        wmove(window,0,i);
        wprintw(window,"=");
    }
        
    
}