/**
 * @file player.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include "player.h"
#include "wall.h"
#include "projectile.h"
#include "enemy.h"
#include "myWindow.h"

Player::Player (const int y, const int x, const int h, const int w) : DynamicObject(y, x, PlayerCollider, h, w, '<', '>', 1, 3){}
void Player::reposition(const int yy, const int xx){
    y = yy;
    x = xx;
    _state = Idle;
}

void Player::moveUp(Map m){
    if ( y > 0 
    && dynamic_cast<Bush *>(m.get (y - 1, x)) == nullptr
    && dynamic_cast<Wall *>(m.get (y - 1, x)) == nullptr
    && dynamic_cast<Bullet*>(m.get(y - 1, x)) == nullptr){
        y--;
    } 
}
void Player::moveDown(Map m){
    if (y < height - 1 
    && dynamic_cast<Bush *>(m.get(y + 1, x)) == nullptr
    && dynamic_cast<Wall *>(m.get(y + 1, x)) == nullptr
    && dynamic_cast<Bullet *>(m.get(y + 1, x)) == nullptr){
        y++;
    }  
}
void Player::moveLeft(Map m){
    if (x > 0 
    && dynamic_cast<Bush *>(m.get(y, x - 1)) == nullptr
    && dynamic_cast<Wall *>(m.get(y, x - 1)) == nullptr
    && dynamic_cast<Bullet *>(m.get(y, x - 1)) == nullptr){
        x--;
    }
}
void Player::moveRight(Map m){
    if (x < width - 1 
    && dynamic_cast<Bush *>(m.get(y, x + 1)) == nullptr 
    && dynamic_cast<Wall *>(m.get(y, x + 1)) == nullptr 
    && dynamic_cast<Bullet *>(m.get(y, x + 1)) == nullptr){
        x++;
    }  
}
int Player::getKey() {

    // if idle, make ready immediately
    if (_state == Idle){
        _updateIndex = 0;
    }


    const int key = getch();
    switch (key)
    {
    case KEY_UP:
    case 'w':
        _state = Up;
        break;
    case KEY_DOWN:
    case 's':
        _state = Down;
        break;
    case KEY_LEFT:
    case 'a':
        _state = Left;
        break;
    case KEY_RIGHT:
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
Projectile * Player::shoot(state dir){
    switch (dir)
    {
    case StateShootingLeft:
        return new Bullet(y, x - 1, height, width, ProjectileLeft);
    case StateShootingRight:
        return new Bullet(y, x + 1, height, width, ProjectileRight);
    case StateShootingUp:
        return new Bullet(y - 1, x, height, width, ProjectileUp);
    case StateShootingDown:
        return new Bullet(y + 1, x, height, width, ProjectileDown);
    default:
        throw invalid_argument("Invalid enum value");
    }
}
state Player::_update(Map & m){
    auto res = Usual;
    if (dir != 0 && _stop){ // stop fast 
        _stop = false;
        int shootY = y;
        int shootX = x;
        switch (_state)
        {
        case Left:
            shootX--;
            res = StateShootingLeft;
            break;
        case Right:
            shootX++;
            res = StateShootingRight;
            break;
        case Up:
            shootY--;
            res = StateShootingUp;
            break;
        case Down:
            shootY++;
            res = StateShootingDown;
            break;
        default:
            throw invalid_argument("Invalid enum value");
        }
        // dont shoot
        
        if (m.check(shootY, shootX) == false
            || m.get(shootY, shootX) != nullptr ){
            res = Usual;
        }

        _state = Idle;
    }
    
    m.set(y, x, nullptr);
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
    
    if (dynamic_cast<Enemy *>(m.get(y, x)) != nullptr ||
        dynamic_cast<Lava *>(m.get(y, x)) != nullptr){
        return GG;
    }
    if (dynamic_cast<Checkpoint *>(m.get(y, x)) != nullptr){
        return NextLevel;
    }
    
    m.set(y, x, (Object*)this);

    if (_stop){ // stop slow delayed if starting to move from idle
        _state= Idle;
        _stop = false;
     }

    return res;
}
bool Player::isDangerous() const{
    return false;
}