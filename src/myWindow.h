/**
 * @file wall.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>

class MyWindow {
    public:
        MyWindow ();
        void draw(const int y, const int x, const char charLeft, const char charRight, const int color);
        void initLevel();
        void resize(const int height, const int width);
        void getSize(int & height, int & width) const;
        void refreshWindow();
        void endLevel();
    private:
        WINDOW * win = nullptr;
};
