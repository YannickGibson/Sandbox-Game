include <iostream>
using namespace std;
#include "gameobject.h"

class Map{
    public:
        virtual void collides(const int y, const int x) = 0;
    private:
        vector<vector<bool>> _matrix;
};
class BlockMap{
  void collides(const int y, const int x) {
      if (x < 0 || x > _matrix[0].size() ||
        y < 0 || y > _matrix.size()){
            return false;
        }
      return _matrix(y, x);
  }
};