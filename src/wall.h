/**
 * @file wall.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>
#include "gameobject.h"

class Wall : public StaticObject{
    public:
        Wall (WINDOW * const w, const int y, const int x);
};
