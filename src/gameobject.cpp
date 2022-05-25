/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <curses.h>
#include "gameobject.h"
#include "map.h"



Object::Object(const int yy, const int xx, collision col, WINDOW * const w, const char cl, const char cr, const int clr) :  y(yy), x(xx), collider(col), win(w), charLeft(cl), charRight(cr), color(clr){
    getmaxyx(w, height, width);
    width /= 2; // tile width
    width  -= 1; // borders 
    height -= 2; // borders
}
void Object::_display(){
    wattron(win, COLOR_PAIR(color));

    mvwaddch(win, (y + 1), (x * 2 + 1), charLeft);
    mvwaddch(win, (y + 1), (x * 2 + 1) + 1, charRight);
    //mvwaddch(win, (y + 1), (x * 2 + 1), ' ');
    //mvwaddch(win, (y + 1), (x * 2 + 1) + 1, ' ');
    wattroff(win, COLOR_PAIR(color));
}

StaticObject::StaticObject(const int yy, const int xx, collision col, WINDOW * const w, const char cl, const char cr, const int clr) :  Object(yy, xx, col, w, cl, cr, clr){
    _display();
}

DynamicObject::DynamicObject(const int yy, const int xx, collision col, WINDOW * const w, const char cl, const char cr, const int clr, const int uSpeed, const bool updateInstantly) : Object(yy, xx, col, w, cl, cr, clr), updateSpeed(uSpeed), _killed(false) {
    if (updateInstantly)
        _updateIndex = 0;
    else
        _updateIndex = updateSpeed;
}
void DynamicObject::_removeTraces(){
    mvwaddch(win, (y + 1), (x * 2 + 1), ' ');
    mvwaddch(win, (y + 1), (x * 2 + 1) + 1, ' ');
}
state DynamicObject::update(Map & m){
    if (_killed == true){
        return GG;
    }
    state res = Usual;
    if (_updateIndex <= 0){
        _updateIndex = updateSpeed;
        _removeTraces();
        res = _update(m);
    }
    else{
        _updateIndex--;
    }

    if (res != GG)
        _display();
    return res;
}

void DynamicObject::kill(Map & m){
    _killed = true;
    _removeTraces();
    m.set(y, x, nullptr);
}