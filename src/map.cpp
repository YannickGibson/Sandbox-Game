/**
 * @file map.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <vector>
#include <iostream>
#include "map.h"
#include "enemy.h"
#include "myWindow.h"

using namespace std;

Map::Map(size_t height, size_t width, MyWindow * w): win(w){
    vector<DynamicObject *> dynamicObjects;
    vector<StaticObject *> staticObjects;
}
void Map::_initMatrix(size_t height, size_t width){
    _matrix = vector<vector<Object *>>(height);
    for (size_t j = 0; j < height; j++)
    {
        _matrix[j] = vector<Object *>(width);
        for (size_t i = 0; i < width; i++){
            _matrix[j][i] = nullptr;
        }
    }
}
void Map::_addObject(){
    if (name == "Spawn")
    {
        p = new Player(y, x, height, width);
    }
    else if (name == "Wall")
    {
        staticObjects.push_back(new Wall(y, x, height, width));
    }
    else if (name == "Lava")
    {
        staticObjects.push_back(new Lava(y, x, height, width));
    }
    else if (name == "Enemy")
    {
        dynamicObjects.push_back(new Enemy(y, x, height, width));
    }
    else if (name == "Goal")
    {
        staticObjects.push_back(new Checkpoint(y, x, height, width));
    }
    else if (name == "Bush"){
        dynamicObjects.push_back(new Bush(y, x, height, width));
    }
    else if (name == "End")
    {
        endCheck = true;
        break;
    }
    else
    {
        throw invalid_argument("Corrupted reading fxile");
    }
}

void Map::loadMap(){
    _initMatrix();

    string line;
    ifstream myfile("assets//levels/level" + to_string(index));
    bool endCheck = false;
    if (myfile.is_open())
    {

        myfile >> height >> width;
        myWindow.resize(height, width); // resize win before game object inicialization

        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                string name;
                int x;
                int y;
                myfile >> name >> y >> x;
                _addObject();
            }
        }

        myfile.close();
        if (endCheck == false)
        {
            throw invalid_argument("Error loading file");
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