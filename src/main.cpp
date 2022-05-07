#include <iostream>
#include <locale.h>
#include <curses.h>
#include "player.h"
#include <vector>

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

setlocale(LC_CTYPE, "");
    
    initscr();
    refresh();
    noecho();
    curs_set(0); // hide cursor
    nodelay(stdscr, TRUE);
    //scrollok(stdscr, TRUE);


    int stdWidth, stdHeight;
    int width  = 50;
    int height = 20;
    getmaxyx(stdscr, stdHeight, stdWidth);
    WINDOW * win = newwin(height, width, (stdHeight/2) - 10, 10);
    nodelay(win, TRUE);

    box(win, '#', '#');
    refresh();
    wrefresh(win);
    Player * p = new Player(win, 1, 1, '@');
    vector<GameObject *> objects;
    objects.push_back(p);

    do {
        mvwaddch(win, height - 1, width - 1, '┘');


        for (size_t i = 0; i < objects.size(); i++)
        {
            objects[i]->update();
        }
        
        wrefresh(win);
        timeout(70);
    }while(p->getKey() != 'x');

    getch();
    endwin();

}