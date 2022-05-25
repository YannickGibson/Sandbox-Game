/**
 * @file wall.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>
#include "gameobject.h"

class Wall : public StaticObject{
    public:
        Wall (const int y, const int x, WINDOW * const w);
};

class Lava : public StaticObject{
    public:
        Lava (const int y, const int x, WINDOW * const w);
};

class Checkpoint : public StaticObject{
    public:
        Checkpoint (const int y, const int x, WINDOW * const w);
};
