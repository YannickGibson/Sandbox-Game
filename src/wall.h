#include <iostream>
#include <curses.h>
#include "gameobject.h"

class Wall : public GameObject{
    private:
        int x, y, width, height;
};
