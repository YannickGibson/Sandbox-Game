/**
 * @file player.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "map.h"
#include "projectile.h"
#include "myWindow.h"

#pragma once

enum playerDirection {Left, Right, Up, Down, Idle};
class Player : public DynamicObject{
    public:
        Player (const int y, const int x, const int h, const int w );

        /**
         * @brief if possible moves player up 
         *
         */
        void moveUp(Map m);
        /**
         * @brief if possible moves player down 
         *
         */
        void moveDown(Map m);
        /**
         * @brief if possible moves player left
         *
         */
        void moveLeft(Map m);
        /**
         * @brief if possible moves player right 
         *
         */
        void moveRight(Map m);
        /**
         * @brief reads a key input from input source. Functions according to it
         *
         */
        int getKey();
        Projectile * shoot(state x);
        void reposition(const int yy, const int xx);
        bool isDangerous() const override;
    private:
        state _update(Map & m) override;
        bool _stop = false; // for more fluent stopping, makes it delayed
        bool _firstStep = false; // for more fluent stopping, makes it delayed
        int dir = 0; // for more fluent stopping, makes it delayed
        playerDirection _state = Idle;
};
