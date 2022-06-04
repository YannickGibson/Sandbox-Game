/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <curses.h>
#include "myWindow.h"

enum collision {PlayerCollider, EnemyCollider, ProjectileCollider, WallCollider, LavaCollider, BushCollider, CheckpointCollider};

class Map;

class Object {
     public:
        int y;
        int x;
        collision collider;
        Object(const int yy, const int xx, collision col, const int h, const int w, const char cl, const char cr, const int clr);
        virtual ~Object () {};
        /**
         * @brief Display character that represents the object to the window
         *
         */
        void _display(MyWindow & w) const;
        virtual bool isDangerous() const = 0;
    protected:
        int height;
        int width;
        char charLeft;
        char charRight;
        int color;
};
enum state {Usual, GG, NextLevel, TrySpawnBush, StateShootingLeft, StateShootingRight, StateShootingUp, StateShootingDown};
class StaticObject : public Object{
    public:
        StaticObject(const int yy, const int xx, collision col, const int h, const int w, const char cl, const char cr, const int clr);
        virtual ~StaticObject () {};
        void update(MyWindow & w);
};

class DynamicObject : public Object{
    public:
        DynamicObject(const int yy, const int xx, collision col, const int h, const int w, const char cl, const char cr, const int clr, const int uSpeed, const bool updateInstantly = true);
        virtual ~DynamicObject () {};
        /**
         * @brief update that depends on a update logic, calls _update if the logic is satisfied
         *
         */
        state update(Map & m, MyWindow & w);
        void kill(Map & m);
    private:
        /**
         * @brief actual update 
         *
         */
        virtual state _update(Map & m) = 0;
        int updateSpeed = 3;
        bool _killed;
    protected:
        void _removeTraces(MyWindow & w);
        int _updateIndex = 0;
};
