/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <curses.h>

class Map;

class Object {
     public:
        int y;
        int x;
        Object(const int yy, const int xx, WINDOW * const w, const char cl, const char cr);
        virtual ~Object () {};
        /**
         * @brief Display character that represents the object to the window
         *
         */
        void _display();
    protected:
        WINDOW * win;
        char charLeft;
        char charRight;
        int width, height;
};
enum state {Usual, GG, StateShootingLeft, StateShootingRight, StateShootingUp, StateShootingDown};
class StaticObject : public Object{
    public:
        StaticObject(const int yy, const int xx, WINDOW * const w, const char cl, const char cr);
        virtual ~StaticObject () {};
};

class DynamicObject : public Object{
    public:
        DynamicObject(const int yy, const int xx, WINDOW * const w, const char cl, const char cr, const int uSpeed = 3);
        virtual ~DynamicObject () {};
        /**
         * @brief update that depends on a update logic, calls _update if the logic is satisfied
         *
         */
        state update(Map & m);
    private:
        /**
         * @brief actual update 
         *
         */
        virtual state _update(Map & m) = 0;
        virtual void _removeTraces();
        int updateSpeed = 3;
    protected:
        int updateIndex = 0;
};
