/**
 * @file player.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include "player.h"
#include "projectile.h"
#include "staticObjects.h"

Player::Player (const int y, const int x, const int h, const int w) : DynamicObject(y, x, h, w, '<', '>', 1, 3){}

void Player::moveUp(Map m){
    if ( y > 0 
    && (m.isEmpty(y - 1, x) || m.get(y - 1, x)->isDangerous())){
        y--;
    } 
}
void Player::moveDown(Map m){
    if (y < height - 1 
    && (m.isEmpty(y + 1, x) || m.get(y + 1, x)->isDangerous() )){
        y++;
    }  
}
void Player::moveLeft(Map m){
    if (x > 0 
    &&(m.isEmpty(y, x - 1) || m.get(y, x - 1)->isDangerous() )){
        x--;
    }
}
void Player::moveRight(Map m){
    if (x < width - 1 
    &&(m.isEmpty(y, x + 1) || m.get(y, x + 1)->isDangerous() )){
        x++;
    }  
}
int Player::getKey() {

    // if idle, make ready immediately
    if (_state == Idle){
        _updateIndex = 0;
    }

    const int key = tolower(getch());
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
        _build = false;
        break;
    case 'q':
        _build = true;
        _stop = true;
        break;
    default:
        break;
    }
    return key;
}
void Player::_tryBuildShoot(Map & m) const{
    int instanciateY = y;
    int instanciateX = x;
    projectileState pState;
    switch (_state)
    {
    case Left:
        instanciateX--;
        pState = ProjectileLeft;
        break;
    case Right:
        instanciateX++;
        pState = ProjectileRight;
        break;
    case Up:
        instanciateY--;
        pState = ProjectileUp;
        break;
    case Down:
        instanciateY++;
        pState = ProjectileDown;
        break;
    default:
        throw invalid_argument("Invalid enum value");
    }
    
    if (m.checkBoundaries(instanciateY, instanciateX) && m.isEmpty(instanciateY, instanciateX) ){
        if (_build && m.getScore() >= 5)
        {
            m.add( new Brick(instanciateY, instanciateX, height, width) );
            m.decrementScore();
        }
        else if(!_build){
            m.add(new Bullet(instanciateY, instanciateX, height, width, pState) );

        }
    }
}

void Player::_update(Map & m){
    if (dir != 0 && _stop){ // stop fast ;
        _tryBuildShoot(m);
        _stop = false;
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
    if (!m.isEmpty(y, x)){
        if (m.get(y, x)->isDangerous()){
            kill(m);
        }
    }
    m.set(y, x, (Object*)this);

    if (_stop){ // stop slow delayed if starting to move from idle
        _state= Idle;
        _stop = false;
     }

}
bool Player::isDangerous() const{
    return true;
}
bool Player::isToxic() const{
    return false;
}
std::string Player::getExport() const{
    return "Spawn";
}