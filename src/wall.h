/**
 * @file wall.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "myWindow.h"

class Wall : public StaticObject{
    public:
        Wall (const int y, const int x, const int h, const int w);
        bool isDangerous() const override;
};

class Lava : public StaticObject{
    public:
        Lava (const int y, const int x, const int h, const int w);
        bool isDangerous() const override;
};

class Checkpoint : public StaticObject{
    public:
        Checkpoint (const int y, const int x, const int h, const int w);
        bool isDangerous() const override;
};
