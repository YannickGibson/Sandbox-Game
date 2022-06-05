/**
 * @file projectile.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include "gameobject.h"
#include "map.h"

//! Dictates which way a Projectile flies.
enum projectileState {ProjectileLeft, ProjectileRight, ProjectileUp, ProjectileDown};

//! Abstract class for all Projectiles.
class Projectile : public DynamicObject {
    public:
        Projectile(const int y, const int x, const int h, const int w, const int clr, const projectileState dr);
        virtual ~Projectile () {};
    private:
    protected:
        //! Current direction of Projectile.
        projectileState _dir;
        //! Life span of Projectile. How many calls of _update function till the object ceases to exist.
        int lifespan = 7;
};

//! A common weapon intended for Player
class Bullet : public Projectile {
    private:
        void _update(Map & m) override;
        //! Signals if the bullet was recently spawned.
        bool _spawning = true;
    public:
        Bullet(const int y, const int x, const int h, const int w, const projectileState d);
        //! Tells if the positon collides with anything on the map, kills it or this object according to some logic.
        bool _collides(const int newY, const int newX, Map & m);
        bool isDangerous() const override;
        bool isToxic() const override;
        std::string getExport() const override;
};
