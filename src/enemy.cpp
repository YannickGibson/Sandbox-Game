/**
 * @file enemy.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <time.h>
#include "enemy.h"

Enemy::Enemy (const int y, const int x, const int h, const int w ) : DynamicObject(y, x, h, w, '/', '\\', 2, 3){
    _dir = rand() % 2;
    _horizontal = rand() % 2;
}

bool Enemy::isDangerous() const {
    return true;
}

bool Enemy::isToxic() const{
    return false;
}

std::string Enemy::getExport() const{
    return "Enemy";
}

void Enemy::_newDir(){
    int rnd = rand() % 4;
    switch (rnd)
    {
    case 0:
        _dir = -1;
        _horizontal = 0;
        break;
    case 1:
        _dir = 1;
        _horizontal = 0;
        break;
    case 2:
        _dir = 1;
        _horizontal = 1;
        break;
    case 3:
        _dir = -1;
        _horizontal = 1;
        break;
    default:
        break;
    }
}

void Enemy::_move(const int newY, const int newX, Map & m){
    m.set(y, x, nullptr);
    y = newY;
    x = newX;
    if (!m.isEmpty(y, x)){
        Object * o = m.get(y, x);
        if (o->isDangerous()){
            o->kill(m);
            return;
        }
    }
    m.set(newY, newX, (Object*)this);
}

bool Enemy::_canMove(const int y, const int x, const Map & m) const{
    if ( y < 0 || y >= height || x < 0 || x >= width)
        return false;
    if (rand() % 4 == 0)
        return false;
    if (!m.isEmpty(y, x)){
        Object * o = m.get(y, x);
        if (!o->isDangerous() || o->isToxic())
            return false;
    }
    return true;
}

void Enemy::_update(Map & m){
    int tryCount = 1;
    do
    {
        int newY = y;
        int newX = x;
        if (_horizontal == 1)
            newY += _dir;
        else
            newX += _dir;

        if (!_canMove(newY, newX, m))
            _newDir();
        else
            _move(newY, newX, m);

    } while (++tryCount <= 1);
}
