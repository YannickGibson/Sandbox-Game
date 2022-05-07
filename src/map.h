#include <iostream>
using namespace std;
#pragma once

#include "gameobject.h"

template <typename T>
class Map{
    public:
        virtual void collides(const int y, const int x) = 0;
    private:
        vector<vector<bool>> _matrix;
};
class BlockMap{
  void collides(StaticObject o) {
      if (o->x < 0 || o->x > _matrix[0].size() ||
        o->y < 0 || o->y > _matrix.size()){
            return false;
        }
      return _matrix(y, x);
  }
};