/**
 * @file wall.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>

#include "gameobject.h"
#include "wall.h"


Wall::Wall (const int y, const int x, WINDOW * const w) : StaticObject(y, x, WallCollider, w, '[', ']', 3) { } 

Lava::Lava (const int y, const int x, WINDOW * const w) : StaticObject(y, x, LavaCollider, w, '6', '3', 4) { } 

Checkpoint::Checkpoint (const int y, const int x, WINDOW * const w) : StaticObject(y, x, CheckpointCollider, w, '#', '#', 5) { } 