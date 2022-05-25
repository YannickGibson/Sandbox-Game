/**
 * @file map.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once
#include <iostream>
#include <vector>
#include "gameobject.h"
#include "enemy.h"
using namespace std;


class Map
{   
    private:
        vector<vector<Object *>> _matrix;
        vector<StaticObject *> * _staticObjects;
        vector<DynamicObject *> * _dynamicObjects;
        vector<StaticObject *>  _toAddStatic;
        vector<DynamicObject *>  _toAddDynamic;

        /**
         * @brief checks if the position is available
         *
         */
        void _tryAdd(Object * o);
    public:
      bool check(const int y, const int x) const;
      Map(size_t height, size_t width, vector<StaticObject *> * sta, vector<DynamicObject *> * dyn);
       /**
         *   @brief adds objects to the coresponding positions in the map
         *
         */
        void add(const vector<DynamicObject *> & objects);
        
        void add(const vector<StaticObject *> & objects);
        void add(const Bush * bush);
        void addUpdate();
        
        Object * get(const int y, const int x) const;
        void set(const int y, const int x, Object * const o);

       /**
         * @brief see if the object collides with the map
         *
         */
        bool collides(const StaticObject &o) const;
};
