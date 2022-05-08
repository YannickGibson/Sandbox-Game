/**
 * @file player.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>
#include "gameobject.h"

#pragma once

enum horizontalDirection {Left, Right, IdleH};
enum verticalDirection {Up, Down, IdleV};
class Player : public DynamicObject{
    public:
        Player (WINDOW * const w, const int y, const int x, const char c);

        /**
         * @brief if possible moves player up 
         *
         */
        void moveUp();
        /**
         * @brief if possible moves player down 
         *
         */
        void moveDown();
        /**
         * @brief if possible moves player left
         *
         */
        void moveLeft();
        /**
         * @brief if possible moves player right 
         *
         */
        void moveRight();
        /**
         * @brief reads a key input from input source. Functions according to it
         *
         */
        int getKey();
    private:
        void _update() override;
        bool _stop = false; // for more fluent stopping, makes it delayed
        bool _firstStep = false; // for more fluent stopping, makes it delayed
        int dir = 0; // for more fluent stopping, makes it delayed
        horizontalDirection horizontal = IdleH;
        verticalDirection vertical = IdleV;
};
