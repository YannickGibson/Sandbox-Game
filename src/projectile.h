/**
 * @file projectile.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "map.h"
#include "myWindow.h"


enum projectileState {ProjectileLeft, ProjectileRight, ProjectileUp, ProjectileDown};

class Projectile : public DynamicObject {
    public:
        Projectile(const int y, const int x, const int h, const int w, const int clr, const projectileState dr);
        //virtual state _update(Map m) override;
    private:
    protected:
        int lifespan = 7;
        projectileState _dir;
};


class Bullet : public Projectile {
    private:
        /**
         * @brief updates the bullet, counts in reflecting
         *
         */
        state _update(Map & m) override;
        bool _spawning = true;
    public:
        Bullet(const int y, const int x, const int h, const int w, const projectileState d);
        bool isDangerous() const override;
};
