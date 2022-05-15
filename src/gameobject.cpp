/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <curses.h>
#include "gameobject.h"


Object::Object(const int yy, const int xx, WINDOW * const w, const char cl, const char cr) :  y(yy), x(xx), win(w), charLeft(cl), charRight(cr){
    getmaxyx(w, height, width);
    width /= 2; // tile width
    width  -= 1; // borders 
    height -= 2; // borders
}
void Object::_display(){
    mvwaddch(win, (y + 1), (x * 2 + 1), charLeft);
    mvwaddch(win, (y + 1), (x * 2 + 1) + 1, charRight);
}

StaticObject::StaticObject(const int yy, const int xx, WINDOW * const w, const char cl, const char cr) :  Object(yy, xx, w, cl, cr){
    _display();
}

DynamicObject::DynamicObject(const int yy, const int xx, WINDOW * const w, const char cl, const char cr, const int uSpeed) : Object(yy, xx, w, cl, cr), updateSpeed(uSpeed){
}
void DynamicObject::_removeTraces(){
    mvwaddch(win, (y + 1), (x * 2 + 1), ' ');
    mvwaddch(win, (y + 1), (x * 2 + 1) + 1, ' ');
}
state DynamicObject::update(Map & m){
    state res = Usual;
    if (updateIndex <= 0){
        updateIndex = updateSpeed;
        _removeTraces();
        res = _update(m);
    }
    else{
        updateIndex--;
    }
    _display();
    return res;
}
