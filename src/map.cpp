/**
 * @file map.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <vector>
#include <iostream>
#include "map.h"
#include "enemy.h"

using namespace std;

Map::Map(size_t height, size_t width, vector<StaticObject *> * sta, vector<DynamicObject *> * dyn): _staticObjects(sta), _dynamicObjects(dyn){
    _matrix = vector<vector<Object *>>(height);
    for (size_t j = 0; j < height; j++)
    {
        _matrix[j] = vector<Object *>(width);
        for (size_t i = 0; i < width; i++){
            _matrix[j][i] = nullptr;
        }
    }
}


bool Map::check(const int y, const int x) const
{
    if ( (size_t) x >= 0 && (size_t) x < _matrix[0].size() &&
            ((size_t) y >= 0 && (size_t) y < _matrix.size() ))
    {
        return true;
    } 
    return false;
}

 Object * Map::get(const int y, const int x) const {
    return _matrix[y][x];
 }

 void Map::set(const int y, const int x, Object * const o) {
    _matrix[y][x] = o;
 }

void Map::_tryAdd(Object * o){
    if (check(o->y, o->x))
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

void Map::add(const Bush * bush){
    _tryAdd((Object *) bush);
    _toAddDynamic.push_back((DynamicObject *)bush);
}
void Map::addUpdate(){
    for (size_t i = 0; i < _toAddStatic.size(); i++)
    {
        //_tryAdd((Object *) _toAddStatic[i]);
        _staticObjects->push_back(_toAddStatic[i]);
    }
    _toAddStatic.clear();
    for (size_t i = 0; i < _toAddDynamic.size(); i++)
    {
        //_tryAdd((Object *) _toAddDynamic[i]);
        _dynamicObjects->push_back(_toAddDynamic[i]);
    }
    _toAddDynamic.clear();
}

bool Map::collides(const StaticObject & o) const
{
    if (check(o.y, o.x))
    {
        return false;
    }
    return _matrix[o.y][o.x];
}