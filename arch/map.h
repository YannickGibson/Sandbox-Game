#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

struct Map {
  struct Point {
    friend bool operator == (const Point& a, const Point& b); 
    friend bool operator != (const Point& a, const Point& b); 
    friend bool operator < (const Point& a, const Point& b); 

    friend std::ostream& operator << (std::ostream& out, const Point& p);

    private:
    friend Map;
    Point(int x, int y);

    int x, y;
  };

  enum class PointType : uint8_t {
    Road, Grass, Water, Building
  };

  explicit Map(const std::string& map);

  Point get_point(const std::string& name) const;

  template < typename Fun >
  void for_each_neighbor(const Point& p, Fun f) const {
    // Abychom zachovali zapouzdření, tak funktor f zabalíme
    // do std::function a předáme implementaci. Preferujeme
    // čistotu návrhu před rychlostí.
    for_each_neighbor_impl(p, f);
  } 

  PointType type(const Point& p) const;

  private:
  using Callback = std::function<void(const Point&)>;
  void for_each_neighbor_impl(const Point&, Callback) const;

  std::vector<std::vector<PointType>> _map;
};

