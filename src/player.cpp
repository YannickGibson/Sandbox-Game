/**
 * @file player.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include "player.h"
#include "wall.h"
#include "projectile.h"

Player::Player (const int y, const int x, WINDOW * const w) : DynamicObject(y, x, w, '<', '>'){}
void Player::moveUp(Map m){
    if ( y > 0 
    && dynamic_cast<Wall *>(m.get(y - 1, x)) == nullptr){
        y--;
    } 
}
void Player::moveDown(Map m){
    if (y < height - 1 
    && dynamic_cast<Wall *>(m.get(y + 1, x)) == nullptr){
        y++;
    }  
}
void Player::moveLeft(Map m){
    if (x > 0 
    && dynamic_cast<Wall *>(m.get(y, x - 1)) == nullptr){
        x--;
    }
}
void Player::moveRight(Map m){
    if (x < width - 1 
    && dynamic_cast<Wall *>(m.get(y, x + 1)) == nullptr){
        x++;
    }  
}
int Player::getKey() {

    // if idle, make ready immediately
    if (_state == Idle){
        updateIndex = 0;
    }


    const int key = getch();
    switch (key)
    {
    case 'w':
        _state = Up;
        break;
    case 's':
        _state = Down;
        break;
    case 'a':
        _state = Left;
        break;
    case 'd':
        _state = Right;
        break;
    case ' ':
        _stop = true;
        break;
    default:
        break;
    }
    
    
    return key;
}
Projectile * Player::shoot(state x){
    switch (x)
    {
    case StateShootingLeft:
        return new Bullet(y, x + 1, win, ProjectileDown);
    case StateShootingRight:
        return new Bullet(y, x - 1, win, ProjectileRight);
    case StateShootingUp:
        return new Bullet(y - 1, x, win, ProjectileUp);
    case StateShootingDown:
        return new Bullet(y + 1, x, win, ProjectileDown);
    default:
        throw invalid_argument("Invalid enum value");
    }
}
state Player::_update(Map & m){
    auto res = Usual;
    if (dir != 0 && _stop){ // stop fast 
        _stop = false;
        switch (_state)
        {
        case Left:
            res = StateShootingLeft;
            break;
        case Right:
            res = StateShootingRight;
            break;
        case Up:
            res = StateShootingUp;
            break;
        case Down:
            res = StateShootingDown;
            break;
        default:
            throw invalid_argument("Invalid enum value");
        }

        _state = Idle;
    }
    switch (_state)
    {
    case Up:
        dir = 1;
        moveUp(m);
        break;
    case Down:
        dir = 1;
        moveDown(m);
        break;
    case Left:
        dir = 1;
        moveLeft(m);
        break;
    case Right:
        dir = 1;
        moveRight(m);
        break;
    default:
        dir = 0;
        break;
    }
    if (_stop){ // stop slow delayed if starting to move from idle
        _state= Idle;
        _stop = false;
     }

    return res;
}

