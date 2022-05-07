#include <iostream>
#include <locale.h>
#include <curses.h>
#include "player.h"
#include <vector>
#include <tuple>

using namespace std;

tuple<int, int, WINDOW *> initGame(const int height, const int width){
     initscr();
    setlocale(LC_ALL, "");
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    curs_set(0); // hide cursor
    nodelay(stdscr, TRUE);
    //scrollok(stdscr, TRUE);
    int stdHeight, stdWidth;
    getmaxyx(stdscr, stdHeight, stdWidth);
    WINDOW * win = newwin(height, width, (stdHeight/2) - 10, 10);
    nodelay(win, TRUE);
    return make_tuple(stdHeight, stdWidth, win);
}

int main() {
    /* 
    //attron(A_UNDERLINE);
    printw("Hello world %d %d", yMax, xMax);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    move (2, 8);
    addch('b');
    attroff(COLOR_PAIR(1));
    */

    int width  = 50;
    int height = 20;
    auto [stdWidth, stdHeight, win] = initGame(height, width);
    

    box(win, '#', '#');


    Player * p = new Player(win, 1, 1, '@');
    vector<GameObject *> objects;
    objects.push_back(p);

    do {


        for (size_t i = 0; i < objects.size(); i++)
        {
            objects[i]->update();
        }
        
        mvwaddch(win, height - 1, width - 1, '┘');
        wrefresh(win);
        timeout(70);
    }while(p->getKey() != 'x');

    getch();
    endwin();

}