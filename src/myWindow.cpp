/**
 * @file wall.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>
#include <locale.h>

#include "myWindow.h"



MyWindow::MyWindow () {
    initscr();
    setlocale(LC_ALL, "");
    cbreak();
    noecho();
    //refresh();
    curs_set(0); // hide cursor
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    //scrollok(stdscr, TRUE);

     
    start_color();
    init_pair(1, 1, 0);
    init_pair(2, 0, 13);         // ENEMY
    init_pair(3, 0, COLOR_BLUE); // WALL
    init_pair(4, 0, 9);          // LAVA
    init_pair(5, 0, 11);         // CHECKPOINT
    init_pair(6, 0, COLOR_GREEN);         // BUSH
    init_pair(10, 0, COLOR_CYAN);        // BULLET 

} 
void MyWindow::initLevel(){
    int stdHeight, stdWidth;
    getmaxyx(stdscr, stdHeight, stdWidth);
    // + 2 because of the borders, and 2x for width because thats the tile width
    win = newwin(1 , 1, (stdHeight / 2) - 10, 10);

    nodelay(win, TRUE);

    std::cout << win;
    box(win, '|', '-');
} 

void MyWindow::draw(const int y, const int x, const char charLeft, const char charRight, const int color) {
    wattron(win, COLOR_PAIR(color));
    mvwaddch(win, (y + 1), (x * 2 + 1), charLeft);
    mvwaddch(win, (y + 1), (x * 2 + 1) + 1, charRight);
    wattroff(win, COLOR_PAIR(color));
}

void MyWindow::resize(const int height, const int width){
    wresize(win, height + 2, width * 2 + 2);
}
void MyWindow::getSize(int & height, int & width) const {
    getmaxyx(win, height, width);
    width /= 2; // tile width
    width  -= 1; // borders 
    height -= 2; // borders
}


void MyWindow::refreshWindow(){
    refresh();
    box(win, '|', '-');
    if (win != nullptr){
        //werase(win);
        //wclear(win);
        wrefresh(win);
    }
    int height, width;
    getSize(height, width);
    mvwaddch(win, height - 1, width - 1, '┘');
}

void MyWindow::endLevel(){
    delwin(win);
}