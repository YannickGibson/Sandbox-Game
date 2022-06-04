/**
 * @file wall.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>

#include "gameobject.h"
#include "wall.h"
#include "myWindow.h"


Wall::Wall (const int y, const int x, const int h, const int w) : StaticObject(y, x, WallCollider, h, w, '[', ']', 3) { } 
bool Wall::isDangerous() const{
    return false;
}
Lava::Lava (const int y, const int x, const int h, const int w) : StaticObject(y, x, LavaCollider, h, w, '6', '3', 4) { } 
bool Lava::isDangerous() const{
    return false;
}
Checkpoint::Checkpoint (const int y, const int x, const int h, const int w) : StaticObject(y, x, CheckpointCollider, h, w, '#', '#', 5) { } 
bool Checkpoint::isDangerous() const{
    return false;
}