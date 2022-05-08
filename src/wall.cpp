/**
 * @file wall.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>

#include "gameobject.h"
#include "wall.h"


Wall::Wall (WINDOW * const w, const int y, const int x) : StaticObject(w, y, x, '#') { } 