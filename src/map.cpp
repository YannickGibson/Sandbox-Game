/**
 * @file map.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <fstream>
#include "map.h"
#include "enemy.h"
#include "bush.h"
#include "player.h"

#include <time.h>

using namespace std;

Map::Map(MyWindow * w, const int height, const int width, int * score): _win(w), _height(height), _width(width), _score(score){
    _initMatrix();
}
Map::~Map(){
    for (size_t i=0; i < _dynamicObjects.size(); i++)
    {
        delete _dynamicObjects[i];
    }
    for (size_t i=0; i < _staticObjects.size(); i++)
    {
        delete _staticObjects[i];
    }
}

MyWindow * Map::getWindow() const {
    return _win;
}
void Map::incrementScore(const int inc) {
    (*_score) += inc;
}
void Map::decrementScore() {
    (*_score) -= 5;
    if ((*_score) < 0){
        throw invalid_argument("Score cannot be negative");
    }
}
int Map::getScore(){
    return (*_score);
}

size_t Map::getHeight() const{
    return _height;
}

size_t Map::getWidth() const{
    return _width;
}

void Map::updateStatic(){
    for (size_t i=0; i < _staticObjects.size(); i++)
    {
        _staticObjects[i]->update(*_win);
    }
}

void Map::_trySpawnMobs(const int playerY, const int playerX){
    int y = rand() % getHeight();
    int x = rand() % getWidth();
    if ((x < playerX - spawnRadius || x > playerX + spawnRadius)
        && (y < playerY - spawnRadius || y > playerY + spawnRadius))
    {
        if (isEmpty(y, x)){
            if (rand() % 10 == 0 ){
                add(new Enemy(y, x, getHeight(), getWidth()));
            }
            else if(rand() % 100 == 0 ){
                add(new Bush(y, x, getHeight(), getWidth()));
            }
        }
    }
}

void Map::update(const int playerY, const int playerX){
    for (size_t i=0; i < _dynamicObjects.size(); i++)
    {
        _dynamicObjects[i]->update(*this, *_win);
    }
    _clearUpDead();
    _trySpawnMobs(playerY, playerX);
    _addUpdate();
}



void Map::_clearUpDead(){
    for (auto it = _staticObjects.begin(); it != _staticObjects.end();)
    {
        if ((*it)->isDead())
        {
            delete *it;
            it = _staticObjects.erase(it);
        }
        else
            it++;
    }

    for (auto it = _dynamicObjects.begin(); it != _dynamicObjects.end();)
    {
        if ((*it)->isDead())
        {
            delete *it;
            it = _dynamicObjects.erase(it);
        }
        else
            it++;
    }
}


bool Map::isEmpty(const int y, const int x) const{
    return _matrix[y][x] == nullptr;
}


void Map::_initMatrix(){
    _matrix = vector<vector<Object *>>(_height);
    for (size_t j = 0; j < _height; j++)
    {
        _matrix[j] = vector<Object *>(_width);
        for (size_t i = 0; i < _width; i++)
            _matrix[j][i] = nullptr;
    }
}



bool Map::checkBoundaries(const int y, const int x) const
{
    if (  x >= 0 && x < (int)_width &&
            ( y >= 0 &&  y < (int)_height ))
        return true;
    return false;
}

 Object * Map::get(const int y, const int x) const {
     if (checkBoundaries(y, x) == false){
         throw invalid_argument("Indices out of range");
     }
    return _matrix[y][x];
 }

 void Map::set(const int y, const int x, Object * const o) {
    _matrix[y][x] = o;
 }

void Map::_tryAdd(Object * o){
    if (checkBoundaries(o->y, o->x))
        _matrix[o->y][o->x] = o;
    else
        throw invalid_argument("Object out of range");
}


void Map::add(DynamicObject * obj){
    _tryAdd((Object *) obj);
    _toAddDynamic.push_back(obj);
}
void Map::add(StaticObject * obj){
    _tryAdd((Object *) obj);
    _toAddStatic.push_back(obj);
}

void Map::addNow(DynamicObject * obj){
    _tryAdd((Object *) obj);
    _dynamicObjects.push_back(obj);
}
void Map::addNow(StaticObject * obj){
    _tryAdd((Object *) obj);
    _staticObjects.push_back(obj);
}

void Map::_addUpdate(){
    for (size_t i = 0; i < _toAddStatic.size(); i++)
    {
        _staticObjects.push_back(_toAddStatic[i]);
        _toAddStatic[i]->update(*_win);
    }
    _toAddStatic.clear();
    for (size_t i = 0; i < _toAddDynamic.size(); i++)
    {
        _dynamicObjects.push_back(_toAddDynamic[i]);
    }
    _toAddDynamic.clear();
}

