/**
 * @file myWindow.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>

#include "myWindow.h"


MyWindow::MyWindow(){
    initscr();
    setlocale(LC_ALL, "");
    raw();
    noecho();
    curs_set(0); // hide cursor
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
     
    start_color();
    init_pair(1, 1, 0);
    init_pair(2, 0, 13);          // ENEMY
    init_pair(3, 0, COLOR_BLUE);  // WALL
    init_pair(4, 0, 9);           // LAVA
    init_pair(5, 0, 11);          // CHECKPOINT
    init_pair(6, 0, COLOR_GREEN); // BUSH
    init_pair(10, 0, COLOR_CYAN); // BULLET 

} 
MyWindow::~MyWindow(){
    endwin();
}
void MyWindow::initLevel(){
    if (_win != nullptr)
        delwin(_win);
    _win = newwin(1, 1, 2, 10);
    nodelay(_win, TRUE);
    box(_win, '|', '-');
} 

void MyWindow::draw(const int y, const int x, const char charLeft, const char charRight, const int color) {
    if (_win == nullptr) return;
    wattron(_win, COLOR_PAIR(color));
    mvwaddch(_win, (y + 1), (x * 2 + 1), charLeft);
    mvwaddch(_win, (y + 1), (x * 2 + 1) + 1, charRight);
    wattroff(_win, COLOR_PAIR(color));
}
void MyWindow::resize(const int height, const int width){
    if (_win == nullptr) return;
    wresize(_win, height + 2, width * 2 + 2);
}
void MyWindow::getSize(int & height, int & width) const {
    if (_win == nullptr) {
        height = 0;
        width = 0;
        return;
    }
    getmaxyx(_win, height, width);
    width  /= 2; // tile width
    width  -= 1; // borders 
    height -= 2; // borders
}
void MyWindow::refreshWindow(){
    if (_win == nullptr) return;
    refresh();
    box(_win, '|', '-');
    wrefresh(_win);
}

void MyWindow::endLevel(){
    if (_win != nullptr){
        erase(); // clear stdscr
        delwin(_win);
        _win = nullptr;
    }
}
void MyWindow::updateStatusBar(const int index, const int score) const{
    mvprintw(0, 0, "Score: %d ", score);
    if (index == -1)
        mvprintw(1, 0, "Map: Loaded");
    else
        mvprintw(1, 0, "Map: %d", index);
}
void MyWindow::updateBottomBar() const{
    int height, width;
    getSize(height, width);
    mvprintw(height + 2 + 2 + 1, 0, "Press X to exit | Press Y to save");
}