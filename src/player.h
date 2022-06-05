/**
 * @file player.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "map.h"

//! Indicates which way Player is facing
enum playerDirection {Left, Right, Up, Down, Idle};
//! Class object controlled by user.
class Player : public DynamicObject{
    public:
        Player (const int y, const int x, const int h, const int w );
        //! If possible moves player up.
        void moveUp(Map m);
        //! If possible moves player down.
        void moveDown(Map m);
        //! If possible moves player left.
        void moveLeft(Map m);
        //! If possible moves player right.
        void moveRight(Map m);
        //! Gets key from user
        int getKey();
        bool isDangerous() const override;
        bool isToxic() const override;
        std::string getExport() const override;
    private:
        //! Tries to build or shoot. Depends on _build variable and on what lies on the position.
        void _tryBuildShoot(Map & m) const;
        void _update(Map & m) override;
        //! For more fluent stopping. 
        bool _stop = false;
        //! For more fluent stopping. 
        bool _firstStep = false; 
        //! Helps with fluent stopping
        int dir = 0;
        //! Player direction
        playerDirection _state = Idle;
        //! Either is can shoot or build at stopping
        bool _build = false;
};
