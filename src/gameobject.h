/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <curses.h>

#pragma once

class Object {
     public:
        Object(WINDOW * const w, const int yy, const int xx, const char c);
        virtual ~Object () {};
        /**
         * @brief Display character that represents the object to the window
         *
         */
        void _display();
    protected:
        WINDOW * win;
        int y;
        int x;
        char character;
        int width, height;
};

class StaticObject : public Object{
    public:
        StaticObject(WINDOW * const w, const int yy, const int xx, const char c);
        virtual ~StaticObject () {};
};

class DynamicObject : public Object{
    public:
        DynamicObject( WINDOW * const w, const int yy, const int xx, const char c, const int uSpeed = 3);
        virtual ~DynamicObject () {};
        /**
         * @brief update that depends on a update logic, calls _update if the logic is satisfied
         *
         */
        void update();
    private:
        /**
         * @brief actual update 
         *
         */
        virtual void _update() = 0;
        int updateSpeed = 3;
    protected:
        int updateIndex = 0;
};
