/**
 * @file loader.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <fstream>
#include "gameobject.h"
#include "map.h"
#include "player.h"

//! Class to load and save Map.
class Loader{
    public:
        //! Loads a Map and inicializes necessary methods and functions
        Map * load(int index, int & score, MyWindow & myWindow);
        //! Saves current state of the Map.
        void save(Map & m, const int score) const;
        //! Returns Player pointer, which is saved while calling load().
        Player * getPlayer() const;
    private:
        //! Writes objects to a given stream.
        void _writeObjects(Map & m, ofstream & out) const; 
        //! Adds objects to a given Map
        void _addObject(string name, const int y, const int x, Map & m);
        //! Pointer which is used in getPlayer function, meant to be called after load() method.
        Player * _player = nullptr;
};