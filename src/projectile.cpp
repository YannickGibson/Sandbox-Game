/**
 * @file projectile.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */


#include "projectile.h"
#include <iostream>
#include <curses.h>
#include "wall.h"
#include "enemy.h"

Projectile::Projectile(const int y, const int x, WINDOW * const w, const int clr, const projectileState d) : DynamicObject(y, x, ProjectileCollider, w, '[', ']', clr, 1), _dir(d) {}

Bullet::Bullet(const int y, const int x, WINDOW * const w, const projectileState d) : Projectile (y, x, w, 10, d) {}

state Bullet::_update(Map & m){
    if (_spawning == false)
    {
        if (lifespan-- <= 0){
            m.set(y, x, nullptr);
            return GG;
        }
        int newY = y;
        int newX = x;
        switch (_dir)
        {
        case ProjectileLeft:
            newX--;
            break;
        case ProjectileRight:
            newX++;
            break;
        case ProjectileUp:
            newY--;
            break;
        case ProjectileDown:
            newY++;
            break;
        }

        m.set(y, x, nullptr);

        if (newY < 0 || newY >= height || newX < 0 || newX >= width
            ||  dynamic_cast<Lava *>( m.get(newY, newX) ) || dynamic_cast<Wall *>( m.get(newY, newX) ) ||  dynamic_cast<Checkpoint *>( m.get(newY, newX) )){
            return GG;
        }
        auto enemy = dynamic_cast<Enemy *>( m.get(newY, newX) );
        if (enemy != nullptr){
            enemy->kill(m);
            return GG;
        }
        auto bush = dynamic_cast<Bush *>( m.get(newY, newX) );
        if (bush != nullptr){
            bush->kill(m);
            return GG;
        }

        x = newX;
        y = newY;
    }   
    else
        _spawning = false;
    m.set(y, x, (Object *) this);
    return Usual;
}

