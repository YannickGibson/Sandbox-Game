#include <curses.h>

class GameObject{
    public:
        GameObject(const int y, const int x, WINDOW * w, const int uIndex = 3) : {
            updateSpeed = uIndex;
        }
        virtual void _display() = 0;
        virtual void _update() = 0;
        void update(){
            if (updateIndex <= 0){
                updateIndex = updateSpeed;
                _update();
            }
            else{
                updateIndex--;
            }
            _display();
        }

    private:
        int updateSpeed = 3;
    protected:
        int x, y;
        WINDOW * w;
        int updateIndex = 0;
};