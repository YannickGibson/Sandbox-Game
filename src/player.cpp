#include "player.h"

Player::Player(WINDOW * const w, const int y, const int x, const char c){
    this->win = w;
    this->y = y;
    this->x = x;
    getmaxyx(w, height, width);
    character = c;
}
void Player::moveUp(){
    if (y > 1){
        y--;
    }  
}
void Player::moveDown(){
    if (y < height - 2){
        y++;
    }  
}
void Player::moveLeft(){
    if (x > 1){
        x--;
        x--;
    }  
}
void Player::moveRight(){
    if (x < width - 2){
        x++;
        x++;
    }  
}
int Player::getKey() {

    // if idle, make ready immediately
    if (horizontal == IdleH && vertical == IdleV){
        updateIndex = 0;
    }


    const int key = getch();
    switch (key)
    {
    case 'w':
        horizontal = IdleH;
        if (vertical == Up){
        } 
        else{
        }
        vertical = Up;
        break;
    case 's':
        horizontal = IdleH;
        if (vertical == Down){
        } 
        vertical = Down;
        break;
    case 'a':
        vertical = IdleV;
        if (horizontal == Left){
        } 
        horizontal = Left;
        break;
    case 'd':
        vertical = IdleV;
        if (horizontal == Right){
        } 
        horizontal = Right;
        break;
    case ' ':
        _stop = true;
        break;
    default:
        break;
    }
    
    
    return key;
}
void Player::_update(){
    mvwaddch(win, y, x, ' ');
    if (dir != 0 && _stop){ // stop fast 
        vertical = IdleV;
        horizontal = IdleH;
        _stop = false;
    }
    switch (vertical)
    {
    case Up:
        if (dir == 1){

        }
        dir = 1;
        moveUp();
        break;
    case Down:
        dir = -1;
        moveDown();
        break;
    default:
        dir = 3;
        break;
    }
    switch (horizontal)
    {
    case Left:
        dir = 2;
        moveLeft();
        break;
    case Right:
        dir = -2;
        moveRight();
        break;
    default:
        if (dir == 3)
            dir = 0;
        break;
    }
    if (_stop){ // stop slow delayed if starting to move from idle
        vertical = IdleV;
        horizontal = IdleH;
        _stop = false;
     }
}

void Player::_display(){
    mvwaddch(win, y, x, character);
}