/**
 * @file bush.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <time.h>
#include "bush.h"


Bush::Bush (const int y, const int x, const int h, const int w ) : DynamicObject(y, x, h, w, '}', '{', 6, 50, false){}

bool Bush::isDangerous() const{
    return false;
}
bool Bush::isToxic() const{
    return true;
}
std::string Bush::getExport() const{
    return "Bush";
}

void Bush::_update(Map & m){
    if (_lifespan-- <= 0 || ( _lifespan <= 2 && rand() % 2 == 0 )){
        kill(m);
        return;
    }

    if (m.checkBoundaries(y, x + 1) && m.isEmpty(y, x + 1) ){
        Bush * newBush = new Bush(y, x + 1, height, width);
        m.add(newBush);
    }
    if (m.checkBoundaries(y + 1, x) && m.isEmpty(y + 1, x) ){
        Bush * newBush = new Bush(y + 1, x, height, width);
        m.add(newBush);
    }
    if (m.checkBoundaries(y, x - 1) && m.isEmpty(y, x - 1) ){
        Bush * newBush = new Bush(y, x - 1, height, width);
        m.add(newBush);
    }
    else if (m.checkBoundaries(y - 1, x) && m.isEmpty(y - 1, x) ){
        Bush * newBush = new Bush(y - 1, x, height, width);
        m.add(newBush);
    }
}


