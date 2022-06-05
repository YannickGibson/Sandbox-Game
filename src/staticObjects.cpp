/**
 * @file staticObjects.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */


#include "staticObjects.h"


Wall::Wall   (const int y, const int x, const int h, const int w) : StaticObject(y, x, h, w, '[', ']', 3) { } 
Lava::Lava   (const int y, const int x, const int h, const int w) : StaticObject(y, x, h, w, '6', '3', 4) { } 
Brick::Brick (const int y, const int x, const int h, const int w) : StaticObject(y, x, h, w, '#', '#', 5) { } 

bool Wall::isDangerous() const{
    return false;
}
bool Lava::isDangerous() const{
    return true;
}
bool Brick::isDangerous() const{
    return false;
}

std::string Brick::getExport() const{
    return "Brick";
}
std::string Lava::getExport() const{
    return "Lava";
}
std::string Wall::getExport() const{
    return "Wall";
}

bool Brick::isToxic() const{
    return true;
}
bool Lava::isToxic() const{
    return true;
}
bool Wall::isToxic() const{
    return false;
}