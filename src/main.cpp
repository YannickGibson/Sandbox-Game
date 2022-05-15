/**
 * @file main.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <locale.h>
#include <curses.h>
#include "wall.h"
#include "player.h"
#include <vector>
#include <tuple>
#include "map.h"
#include "projectile.h"

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
    // + 2 because of the borders, and 2x for width because thats the tile width
    WINDOW * win = newwin(height + 2, width * 2 + 2, (stdHeight/2) - 10, 10);
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

    int height = 15;
    int width  = 20;
    auto [stdHeight, stdWidth, win] = initGame(height, width);
    

    box(win, '#', '#');


    vector<DynamicObject *> dynamicObjects;
    Player * p = new Player(1, 1, win);
    
    vector<StaticObject *> staticObjects;
    staticObjects.emplace_back(new Wall(10, 0, win));
    staticObjects.emplace_back(new Wall(10, 1, win));
    staticObjects.emplace_back(new Wall(10, 2, win));
    staticObjects.emplace_back(new Wall(10, 3, win));
    staticObjects.emplace_back(new Wall(10, 4, win));

    Map matrix (height, width);
    matrix.add(dynamicObjects);
    matrix.add(staticObjects);
 
    // refreshing loop
    do {
        for (size_t i = 0; i < dynamicObjects.size(); i++)
        {
            dynamicObjects[i]->update(matrix);
        }
        if (p->update(matrix) == GG){
            // reset level
        }





        mvwaddch(win, height - 1, width - 1, '┘');
        wrefresh(win);
        timeout(70);
    }while(p->getKey() != 'x');

    
    getch();
    endwin();
}