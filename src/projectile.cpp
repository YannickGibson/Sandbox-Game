/**
 * @file projectile.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */


#include "projectile.h"

Projectile::Projectile(const int y, const int x, const int h, const int w, const int clr, const projectileState d)
 : DynamicObject(y, x, h, w, '[', ']', clr, 1), _dir(d) {}

Bullet::Bullet(const int y, const int x, const int h, const int w, const projectileState d) : Projectile (y, x, h, w, 10, d) {}

bool Bullet::_collides(const int newY, const int newX, Map & m){
    if (newY < 0 || newY >= height || newX < 0 || newX >= width ){
        kill(m);
        return true;
    }
    else if (!m.isEmpty(newY, newX)){
        Object * o = m.get(newY, newX);
        if ((!o->isDangerous() && !o->isToxic()) || (o->isDangerous() && o->isToxic())){
            kill(m);
            return true;
        }
        else if((o->isDangerous() && !o->isToxic())){
            o->kill(m);
            kill(m);
            m.incrementScore();
            return true;
        }
        else if (!o->isDangerous() && o->isToxic()){
            o->kill(m);
            kill(m);
            return true;
        }
    }
    return false;
}

void Bullet::_update(Map & m){
    if (_spawning == false)
    {
        m.set(y, x, nullptr);
        if (lifespan-- <= 0){
            this->kill(m);
            return;
        }
        int newY = y;
        int newX = x;
        switch (_dir)
        {
        case ProjectileLeft:
            newX--;
            break;
        case ProjectileRight:
            newX++;
            break;
        case ProjectileUp:
            newY--;
            break;
        case ProjectileDown:
            newY++;
            break;
        }
        if (_collides(newY, newX, m))
            return;
        x = newX;
        y = newY;
    }   
    else
        _spawning = false;
    m.set(y, x, (Object *) this);
}
bool Bullet::isDangerous() const{
    return false;;
}
bool Bullet::isToxic() const{
    return true;
}
std::string Bullet::getExport() const{
    return "Bullet";
}
