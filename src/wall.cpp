/**
 * @file wall.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>

#include "gameobject.h"
#include "wall.h"


Wall::Wall (const int y, const int x, WINDOW * const w) : StaticObject(y, x, w, '#', '#') { } 