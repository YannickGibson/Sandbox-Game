/**
 * @file Enemy.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "map.h"
#include "myWindow.h"


//enum enemyDirection {Left, Right, Up, Down, Idle};
class Enemy : public DynamicObject{
    public:
        Enemy (const int y, const int x, const int h, const int w );
        bool isDangerous() const override;
    private:
        state _update(Map & m) override;
        int _dir;
        int _horizontal;
};

class Bush : public DynamicObject{
    public:
        Bush (const int y, const int x, const int h, const int w );
        Bush * trySpawnBush(Map & m) const;
    private:
        bool isDangerous() const override;
        state _update(Map & m) override;
        int _lifespan = 2;
};
