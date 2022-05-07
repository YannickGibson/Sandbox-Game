#include <iostream>
#include <curses.h>
#include "gameobject.h"

#pragma once

enum horizontalDirection {Left, Right, IdleH};
enum verticalDirection {Up, Down, IdleV};
class Player : public DynamicObject{
    public:
        Player (WINDOW * const w, const int y, const int x, const char c);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        int getKey();
    private:
        void _update();
        void _display();
        bool _stop = false; // for more fluent stopping, makes it delayed
        bool _firstStep = false; // for more fluent stopping, makes it delayed
        int dir = 0; // for more fluent stopping, makes it delayed
        horizontalDirection horizontal = IdleH;
        verticalDirection vertical = IdleV;
};
