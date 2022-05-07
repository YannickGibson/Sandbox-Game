#pragma once

#include "map.h"

struct Vehicle {
  virtual ~Vehicle() = default;
  virtual bool can_use(const Map&, const Map::Point&) const = 0;

  // TODO
};

struct Car : Vehicle{
  bool can_use(const Map&, const Map::Point&) const override;
};

struct OffroadCar : Vehicle {
  // Jezdí po cestách a trávě
  bool can_use(const Map&, const Map::Point&) const override;
  // TODO
};

struct Hovercraft {
  // Jezdí všude mimo budovy
  // TODO
};

