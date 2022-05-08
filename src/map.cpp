#include "map.h"
#include <vector>

#include <iostream>
using namespace std;


template <typename T>
bool Map<T>::_check(const int y, const int x) const
{
    if ( x > 1 && x < _matrix[0].size() - 2 &&
            y > 1 || y < _matrix.size() - 2)
    {
        return true;
    } 
    return false;
}

template <typename T>
Map<T>::Map(const vector<Object *> objects)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        StaticObject * o = objects[i];
        if (_check(o->x, o->x)){

        }
        else{
            throw invalid_argument("Object out of range");
        }
    }
}

template <typename T>
bool Map<T>::collides(StaticObject &o) const
{
    if (_check(o.y, o.x))
    {
        return false;
    }
    return _matrix[o.y, o.x];
}