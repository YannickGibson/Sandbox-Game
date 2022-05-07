#include <iostream>
#include <curses.h>
#include "player.h"

using namespace std;


int main() {
    /* cout << "Lets go nigga" << endl;
    initscr();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    //raw();
    //cbreak();
    //attron(A_UNDERLINE);
    printw("Hello world %d %d", yMax, xMax);
    WINDOW * win = newwin(10, 20, 10, 10);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    move (2, 8);
    addch('b');

    attroff(COLOR_PAIR(1));

    getch();
    endwin(); */

    
    initscr();
    refresh();
    noecho();
    curs_set(0); // hide cursor

    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);


    int stdWidth, stdHeight;
    int width  = 50;
    int height = 20;
    getmaxyx(stdscr, stdHeight, stdWidth);
    WINDOW * win = newwin(height, width, (stdHeight/2) - 10, 10);
    nodelay(win, TRUE);

    box(win, 0, 0);
    refresh();
    wrefresh(win);

    Player * p = new Player(win, 1, 1, '@');

    do {
        p->display();
        wrefresh(win);
        mvwaddch(win, height - 1, width - 1, '┘');
        timeout(100);
    }while(p->getKeyUpdate() != 'x');

    getch();
    endwin();

}