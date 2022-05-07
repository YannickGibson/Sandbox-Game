#include "map.h"

#include <map>
#include <stdexcept>
#include <vector>


/// Point

Map::Point::Point(int x, int y) : x(x), y(y) {}

bool operator == (const Map::Point& a, const Map::Point& b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (const Map::Point& a, const Map::Point& b) {
  return !(a == b);
}

bool operator < (const Map::Point& a, const Map::Point& b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::ostream& operator << (std::ostream& out, const Map::Point& p) {
  return out << p.x << "," << p.y;
}


/// Map

Map::Map(const std::string& map) {
  static const std::map<char, PointType> char_to_type = {
    { 'r', PointType::Road },
    { ' ', PointType::Grass },
    { 'w', PointType::Water },
    { 'b', PointType::Building },
  };

  _map.emplace_back();
  auto *cur_row = &_map.back();

  for (char c : map) {
    if (c == '\n') {
      _map.emplace_back();
      cur_row = &_map.back();
      continue;
    }

    cur_row->push_back(char_to_type.at(c));
  }
}

Map::Point Map::get_point(const std::string& name) const {
  if (name == "start") return Point{0, 0};
  if (name == "end")
    return Point{(int)_map.size() - 1, (int)_map.back().size() - 1};

  throw std::out_of_range("Uknown location");
}

Map::PointType Map::type(const Point& p) const {
  return _map.at(p.x).at(p.y);
}

void Map::for_each_neighbor_impl(const Point& p, Callback cb) const {
  for (auto [xd, yd] : { std::pair<int, int>{-1,0}, {0,-1}, {1, 0}, {0, 1} }) {
    int x = p.x + xd;
    int y = p.y + yd;
    if (x < 0 || x >= (int)_map.size()) continue;
    auto& row = _map[x];
    if (y < 0 || y >= (int)row.size()) continue;
    cb(Point{x, y});
  }
}

