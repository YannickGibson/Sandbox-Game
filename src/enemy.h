/**
 * @file enemy.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include "gameobject.h"
#include "map.h"

//! Moving enemy of main Player, does not collide with Lava.
class Enemy : public DynamicObject{
    public:
        Enemy (const int y, const int x, const int h, const int w );
        bool isDangerous() const override;
        bool isToxic() const override;
        std::string getExport() const override;
    private:
        void _update(Map & m) override;
        //! Chooses a direction for Enemy.
        void _newDir();
        //! Moves a Enemy object if possible or kills it.
        void _move(const int newY, const int newX, Map & m);
        //! Tells if object can be killed, can move or randomly won't move on a desired spot.
        bool _canMove(const int y, const int x, const Map & m) const;
        //! Current direction for object.
        int _dir;
        //! Flag that tells if object is moving horizontaly or verticaly
        int _horizontal;
};
