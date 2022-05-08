
#pragma once
#include <iostream>
#include <vector>
#include "gameobject.h"
using namespace std;

template <typename T>
class Map
{   
    private:
        vector<vector<T>> _matrix;
        bool _check(const int y, const int x) const;
    public:
        Map(const vector<Object *> objects);
        bool collides(StaticObject &o) const;
};
