/**
 * @file map.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

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
        /**
         * @brief checks if the position is available
         *
         */
        bool _check(const int y, const int x) const;
    public:
        Map(const vector<Object *> objects);
        /**
         * @brief see if the object collides with the map
         *
         */
        bool collides(const StaticObject &o) const;
};
