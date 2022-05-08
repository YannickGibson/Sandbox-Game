/**
 * @file projectile.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */


#include <iostream>
#include <curses.h>
#include "gameobject.h"
#pragma once

class Projectile : public DynamicObject{
    private:
        int _dir;
    public:
        Projectile(const int d) : _dir{d}
        virtual ~Projectile () {};

};


class Bullet : public Weapon{
    private:
        /**
         * @brief updates the bullet, counts in reflecting
         *
         */
        void _update() override;
};
