#pragma once

#include <vector>

#include "map.h"
#include "vehicle.h"

std::vector<Map::Point> find_path(const Car& v, const Map& m,
  const std::string& from, const std::string& to);

