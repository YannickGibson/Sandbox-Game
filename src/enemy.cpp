/**
 * @file Enemy.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <curses.h>
#include "gameobject.h"
#include "map.h"
#include "projectile.h"
#include "enemy.h"
#include "player.h"
#include "wall.h"

#include <time.h>

Enemy::Enemy (const int y, const int x, WINDOW * const w ) : DynamicObject(y, x, EnemyCollider, w, '/', '\\', 2, 3){
    _dir = rand() % 2;
    _horizontal = rand() % 2;
}

state Enemy::_update(Map & m){
    int newY;
    int newX;
    int tryCount = 1;
    do
    {
        newY = y;
        newX = x;
        if (_horizontal == 1)
            newY += _dir;
        else
            newX += _dir;
        if (newY < 0 || newY >= height || newX < 0 || newX >= width
            || (m.get(newY, newX) != nullptr && dynamic_cast<Player *>(m.get(newY, newX)) == nullptr && dynamic_cast<Projectile *>(m.get(newY, newX)) == nullptr) /* is not empty */
            || rand() % 4 == 0){
            // cant go
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
        else{
            // MOVE ENEMY
            m.set(y, x, nullptr);
            y = newY;
            x = newX;
            auto projectile = dynamic_cast<Projectile *>(m.get(newY, newX));
            if (projectile  != nullptr){
                projectile->kill(m);
                return GG;
            }
            auto player = dynamic_cast<Player *>(m.get(newY, newX));
            if (player != nullptr){
                player->kill(m);
                return GG;
            }
            m.set(newY, newX, (Object*)this);
            return Usual;
        }
    } while (++tryCount <= 1);
    // stationary
    return Usual;
}

Bush::Bush (const int y, const int x, WINDOW * const w ) : DynamicObject(y, x, BushCollider, w, '}', '{', 6, 50, false){}
Bush * Bush::trySpawnBush(Map & m) const {
    return nullptr;   
}
state Bush::_update(Map & m){
    if (_lifespan-- <= 0 || (_lifespan < 1 && rand() % 2 == 0 )){
        this->kill(m);
        return GG;
    }

    if (m.check(y, x + 1) && m.get(y, x + 1) == nullptr){
        Bush * newBush = new Bush(y, x + 1, win);
        m.add(newBush);
    }
    else if (m.check(y + 1, x) && m.get(y + 1, x) == nullptr){
        Bush * newBush = new Bush(y + 1, x, win);
        m.add(newBush);
    }
    else if (m.check(y, x - 1) && m.get(y, x - 1) == nullptr){
        Bush * newBush = new Bush(y, x - 1, win);
        m.add(newBush);
    }
    else if (m.check(y - 1, x) && m.get(y - 1, x) == nullptr){
        Bush * newBush = new Bush(y - 1, x, win);
        m.add(newBush);
    }
    return Usual;
}
