#include <iostream>
#include <curses.h>
#include "gameobject.h"

class Weapon : public GameObject{
    private:
        virtual void _update();
        virtual void _display();
        char character;
        int x, y, width, height;
        WINDOW * win;
};


class Bullet : public Weapon{
    private:
        void _update();
        void _display();
        char character;
        int x, y, width, height;
        WINDOW * win;
};
