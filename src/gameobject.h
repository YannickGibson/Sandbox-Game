#include <curses.h>

#pragma once

class Object {
     public:
        Object(WINDOW * const w, const int yy, const int xx, const char c);
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
};

class DynamicObject : public Object{
    public:
        virtual void _update() = 0;
        DynamicObject( WINDOW * const w, const int yy, const int xx, const char c, const int uSpeed = 3);
        void update();
    private:
        int updateSpeed = 3;
    protected:
        int updateIndex = 0;
};
