/**
 * @file map.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once
#include <iostream>
#include <vector>
#include "gameobject.h"
#include "myWindow.h"
using namespace std;

//! Represents game world.
class Map
{   
    private:
        //! Checks if the position is available.
        void _tryAdd(Object * o);
        //! Inits matrix to be empty.
        void _initMatrix();
        //! Adds objects to _staticObjects & _dynamicObjects, updates only every StaticObject that was added.
        void _addUpdate();
        //! Clears up objects marked as killed.
        void _clearUpDead();
        //! Tries to spawn mobs that are at least spawnRadius (box) away from coordinates.
        void _trySpawnMobs(const int playerY, const int playerX);
        //! Matrix which allows constant access to Object *.
        vector<vector<Object *>> _matrix;
        //! Vector to save every StaticObject currently in the game.
        vector<StaticObject *> _staticObjects;
        //! Vector to save every DynamicObject currently in the game.
        vector<DynamicObject *> _dynamicObjects;
        //! Vector that adds every StaticObject to _staticObjects after a frame.
        vector<StaticObject *>  _toAddStatic;
        //! Vector that adds every DynamicObject to _dynamicObjects after a frame.
        vector<DynamicObject *>  _toAddDynamic;
        //! Pointer to the screen where Map is represented.
        MyWindow * _win;
    public:
        //! Inicializes necesarry components, which includes _matrix.
        Map(MyWindow * w, const int height, const int width, int * score);
        //! Frees every object it holds except Player.
        ~Map();
        //! Returns _win.
        MyWindow * getWindow() const;
        //! Adds DynamicObject immediately to the coresponding positions in the Map.
        void addNow(DynamicObject * obj);
        //! Adds StaticObject immediately to the coresponding positions in the Map.
        void addNow(StaticObject * obj);
        //! Adds DynamicObject after a frame to the coresponding positions in the Map.
        void add(DynamicObject * obj);
        //! Adds StaticObject after a frame to the coresponding positions in the Map.
        void add(StaticObject * obj);
        //! Returns what lies in the _matrix on corresponding position.
        Object * get(const int y, const int x) const;
        //! Sets _matrix on supplied position to be a specific pointer.
        void set(const int y, const int x, Object * const o);
        //! See if the object is within the Map.
        bool checkBoundaries(const int y, const int x) const;
        //! Updates only static objects.
        void updateStatic();
        //! Updates every DynamicObject, spawns mobs.
        void update(const int playerY, const int playerX);
        //! Returns height of _matrix.
        size_t getHeight() const;
        //! Returns width of _matrix.
        size_t getWidth() const;
        //! Returns true if position in _matrix is equal to nullptr.
        bool isEmpty(const int y, const int x) const;
        //! Increments _score by amount.
        void incrementScore(const int inc);
        //! Decrements _score by 5.
        void decrementScore();
        //! Returns _score.
        int getScore();
      private:
        //! Height of the Map.
        size_t _height;
        //! Width of the Map.
        size_t _width;
        //! Score of Player.
        int * _score;
        //! Minimum distance to spawn mobs around specified coordinates.
        int spawnRadius = 5;
};
