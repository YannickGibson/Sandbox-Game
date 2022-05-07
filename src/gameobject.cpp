#include <curses.h>
#include "gameobject.h"


Object::Object(WINDOW * const w, const int yy, const int xx, const char c) :  win(w), y(yy), x(xx), character(c){
    getmaxyx(w, height, width);
}
void Object::_display(){
    mvwaddch(win, y, x, character);
}

StaticObject::StaticObject(WINDOW * w, const int yy, const int xx, const char c) :  Object(w, yy, xx, c){
    _display();
}

DynamicObject::DynamicObject(WINDOW * const w, const int yy, const int xx, const char c, const int uSpeed) : Object(w, yy, xx, c), updateSpeed(uSpeed){ }
void DynamicObject::update(){
    if (updateIndex <= 0){
        updateIndex = updateSpeed;
        _update();
    }
    else{
        updateIndex--;
    }
    _display();
}
