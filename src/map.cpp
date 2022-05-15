/**
 * @file map.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <vector>
#include <iostream>
#include "map.h"

using namespace std;

Map::Map(size_t height, size_t width){
    _matrix = vector<vector<Object *>>(height);
    for (size_t i = 0; i < height; i++)
    {
        _matrix[i] = vector<Object *>(width);
    }
    
}

bool Map::_check(const int y, const int x) const
{
    if ( (size_t)x >= 0 && (size_t)x < _matrix[0].size() &&
            ((size_t)y >= 0 || (size_t)y < _matrix.size() ))
    {
        return true;
    } 
    return false;
}

 Object * Map::get(const int y, const int x){
    return _matrix[y][x]; 
 }

void Map::_tryAdd(Object * o){
    if (_check(o->y, o->x))
    {
        _matrix[o->y][o->x] = o;
    }
    else{
        throw invalid_argument("Object out of range");
    }
}

void Map::add(const vector<DynamicObject *> & objects){
    for (size_t i = 0; i < objects.size(); i++)
    {
        _tryAdd(objects[i]);
    }
}
void Map::add(const vector<StaticObject *> & objects){
    for (size_t i = 0; i < objects.size(); i++)
    {
        _tryAdd(objects[i]);
    }
}

bool Map::collides(const StaticObject & o) const
{
    if (_check(o.y, o.x))
    {
        return false;
    }
    return _matrix[o.y][o.x];
}