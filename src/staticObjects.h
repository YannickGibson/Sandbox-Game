/**
 * @file staticObjects.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "myWindow.h"

//! Wall which is a core building block for worlds
class Wall : public StaticObject{
    public:
        Wall (const int y, const int x, const int h, const int w);
        bool isDangerous() const override;
        bool isToxic() const override;
        std::string getExport() const override;
};

//! Lava object which is dangerous to touch to Player
class Lava : public StaticObject{
    public:
        Lava (const int y, const int x, const int h, const int w);
        bool isDangerous() const override;
        bool isToxic() const override;
        std::string getExport() const override;
};

//! Brick which should be used for building by Player
class Brick : public StaticObject{
    public:
        Brick (const int y, const int x, const int h, const int w);
        bool isDangerous() const override;
        bool isToxic() const override;
        std::string getExport() const override;
};
