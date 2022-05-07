#include "vehicle.h"

bool Car::can_use(const Map& map, const Map::Point& p) const {
  return map.type(p) == Map::PointType::Road;
}

bool OffroadCar::can_use(const Map& map, const Map::Point& p) const {
  return map.type(p) == Map::PointType::Road || map.type(p) == Map::PointType::Grass;
}


