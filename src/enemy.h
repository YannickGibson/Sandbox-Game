/**
 * @file Enemy.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "map.h"


//enum enemyDirection {Left, Right, Up, Down, Idle};
class Enemy : public DynamicObject{
    public:
        Enemy (const int y, const int x, WINDOW * const w );
    private:
        state _update(Map & m) override;
        int _dir;
        int _horizontal;
};

class Bush : public DynamicObject{
    public:
        Bush (const int y, const int x, WINDOW * const w );
        Bush * trySpawnBush(Map & m) const;
    private:
        state _update(Map & m) override;
        int _lifespan = 2;
};
