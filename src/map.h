/**
 * @file map.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once
#include <iostream>
#include <vector>
#include "gameobject.h"
using namespace std;


class Map
{   
    private:
        vector<vector<Object *>> _matrix;
        /**
         * @brief checks if the position is available
         *
         */
        bool _check(const int y, const int x) const;
        void _tryAdd(Object * o);
    public:
      Map(size_t height, size_t width);
       /**
         *   @brief adds objects to the coresponding positions in the map
         *
         */
        void add(const vector<DynamicObject *> & objects);
        
        void add(const vector<StaticObject *> & objects);
        
        Object * get(const int y, const int x);

       /**
         * @brief see if the object collides with the map
         *
         */
        bool collides(const StaticObject &o) const;
};
