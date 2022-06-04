/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <curses.h>
#include "gameobject.h"
#include "map.h"
#include "myWindow.h"



Object::Object(const int yy, const int xx, collision col, const int h, const int w, const char cl, const char cr, const int clr) :  y(yy), x(xx), collider(col),height(h), width(w), charLeft(cl), charRight(cr), color(clr){}
void Object::_display(MyWindow & w) const{
    w.draw(y, x, charLeft, charRight, color);
}

StaticObject::StaticObject(const int yy, const int xx, collision col, const int h, const int w, const char cl, const char cr, const int clr) :  Object(yy, xx, col, h, w, cl, cr, clr){}
void StaticObject::update(MyWindow & w){
    _display(w);
}

DynamicObject::DynamicObject(const int yy, const int xx, collision col, const int h, const int w, const char cl, const char cr, const int clr, const int uSpeed, const bool updateInstantly) : Object(yy, xx, col, h, w, cl, cr, clr), updateSpeed(uSpeed), _killed(false) {
    if (updateInstantly)
        _updateIndex = 0;
    else
        _updateIndex = updateSpeed;
}
void DynamicObject::_removeTraces(MyWindow & w){ //DELETE ME
    w.draw(y, x, ' ', ' ', 0);
}
state DynamicObject::update(Map & m, MyWindow & w){
    if (_killed == true){
        return GG;
    }
    state res = Usual;
    if (_updateIndex <= 0){
        _updateIndex = updateSpeed;
        _removeTraces(w);
        res = _update(m);
    }
    else{
        _updateIndex--;
    }

    if (res != GG)
        _display(w);
    return res;
}

void DynamicObject::kill(Map & m){
    _killed = true;
    _removeTraces(*m.win); // dereferencing wont make a copy here
    m.set(y, x, nullptr);
}