#include <iostream>
enum horizontalDirection {Left, Right, IdleH};
enum verticalDirection {Up, Down, IdleV};
class Player{
    public:
        Player(WINDOW * const w, const int y, const int x, const char c);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        int getKeyUpdate();
        void display();
    private:
    char character;
    int x, y, width, height;
    horizontalDirection horizontal = IdleH;
    verticalDirection vertical = IdleV;
    WINDOW * win;
};


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
    }  
}
void Player::moveRight(){
    if (x < width - 2){
        x++;
    }  
}
int Player::getKeyUpdate() {
    const int key = getch();
    mvwaddch(win, y, x, ' ');
    switch (key)
    {
    case 'w':
        if (vertical == Up){
            horizontal = IdleH;
        } 
        vertical = Up;
        break;
    case 's':
        if (vertical == Down){
            horizontal = IdleH;
        } 
        vertical = Down;
        break;
    case 'a':
        if (horizontal == Left){
            vertical = IdleV;
        } 
        horizontal = Left;
        break;
    case 'd':
        if (horizontal == Right){
            vertical = IdleV;
        } 
        horizontal = Right;
        break;
    case ' ':
        vertical = IdleV;
        horizontal = IdleH;
        break;
    default:
        break;
    }
    switch (vertical)
    {
    case Up:
        moveUp();
        break;
    case Down:
        moveDown();
        break;
    default:
        break;
    }
    switch (horizontal)
    {
    case Left:
        moveLeft();
        break;
    case Right:
        moveRight();
        break;
    default:
        break;
    }

    return key;
}

void Player::display(){
    mvwaddch(win, y, x, character);
}