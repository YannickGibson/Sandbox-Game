/**
 * @file myWindow.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>

//: Wrapper for ncurses WINDOW object.
class MyWindow {
    public:
        //! Inicializes standard screen, sets colors.
        MyWindow();
        //! Attempts to handle leaks
        ~MyWindow();
        //! Wrapper for ncurses drawing funcion.
        void draw(const int y, const int x, const char charLeft, const char charRight, const int color);
        //! Inicializes level, by creating a new window and creating a box around it.
        void initLevel();
        //! Resizes _win to a desired size.
        void resize(const int height, const int width);
        //! Adjusts out parameters to contain size of _win.
        void getSize(int & height, int & width) const;
        //! Refreshes window and draws box around it.
        void refreshWindow();
        //! Ends level, gets rid of _win.
        void endLevel();
        
        //! Updates status bar at the top of stdscr.
        void updateStatusBar(const int index, const int score) const;
        //! Updates bottom bar, which should be static.
        void updateBottomBar() const;
    private:
        //! Pointer to inner window in the stdscr
        WINDOW * _win = nullptr;
};
