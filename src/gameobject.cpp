/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include "gameobject.h"
#include "map.h"


Object::Object(const int yy, const int xx, const int h, const int w, const char cl, const char cr, const int clr)
     :  y(yy), x(xx), height(h), width(w), _killed(false), charLeft(cl), charRight(cr), color(clr) {}

void Object::_display(MyWindow & w) const{
    w.draw(y, x, charLeft, charRight, color);
}

void Object::_removeTraces(MyWindow & w) const { //DELETE ME
    w.draw(y, x, ' ', ' ', 0);
}
void Object::kill(Map & m){
    _killed = true;
    _removeTraces(*m.getWindow()); // dereferencing wont make a copy here
    m.set(y, x, nullptr);
}
bool Object::isDead() const {
    return _killed;
}

StaticObject::StaticObject(const int yy, const int xx, const int h, const int w, const char cl, const char cr, const int clr) 
    : Object(yy, xx, h, w, cl, cr, clr) {}

void StaticObject::update(MyWindow & w){
    _display(w);
}

DynamicObject::DynamicObject(const int yy, const int xx, const int h, const int w, const char cl, const char cr, const int clr
    , const int uSpeed, const bool updateInstantly)
    : Object(yy, xx, h, w, cl, cr, clr), updateSpeed(uSpeed)
{
    if (updateInstantly)
        _updateIndex = 0;
    else
        _updateIndex = updateSpeed;
}

void DynamicObject::update(Map & m, MyWindow & w){
    if (_killed == true)
        return;

    if (_updateIndex <= 0){
        _updateIndex = updateSpeed;
        _removeTraces(w);
        _update(m);
    }
    else
        _updateIndex--;

    if (_killed == false)
        _display(w);
}

