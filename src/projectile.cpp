/**
 * @file projectile.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */


#include "projectile.h"
#include <iostream>
#include <curses.h>

Projectile::Projectile(const int y, const int x, WINDOW * const w, const projectileState d) : DynamicObject(y, x, w, '.', '.'), _dir(d){}
Bullet::Bullet(const int y, const int x, WINDOW * const w, const projectileState d) : Projectile (y, x, w, d){}

state Bullet::_update(Map & m){
    return Usual;
}

