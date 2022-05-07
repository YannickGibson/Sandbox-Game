#include <iostream>
#include <curses.h>
#include "gameobject.h"

enum horizontalDirection {Left, Right, IdleH};
enum verticalDirection {Up, Down, IdleV};
class Player : public GameObject{
    public:
        Player(WINDOW * const w, const int y, const int x, const char c);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        int getKey();
    private:
        void _update();
        void _display();
        bool _stop = false; // for more fluent stopping, makes it delayed
        bool _firstStep = false; // for more fluent stopping, makes it delayed
        int dir = 0; // for more fluent stopping, makes it delayed
        char  character;
        int x, y, width, height;
        horizontalDirection horizontal = IdleH;
        verticalDirection vertical = IdleV;
        WINDOW * win;
};
