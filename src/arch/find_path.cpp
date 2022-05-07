#include "find_path.h"

#include <deque>
#include <map>

std::vector<Map::Point> find_path(const Vehicle& v, const Map& map,
  const std::string& from, const std::string& to) {
  using Point = Map::Point;

  Point s = map.get_point(from);
  std::map<Point, Point> pred;
  std::deque<Point> q;
  q.push_back(s);

  while (!q.empty()) {
    Point p = q.front();
    q.pop_front();

    map.for_each_neighbor(p, [&](const Point& u) {
      if (u == s || !v.can_use(map, u) || pred.count(u) != 0) return;
      pred.emplace(u, p);
      q.push_back(u);
    });
  }

  Point t = map.get_point(to);
  std::vector<Point> ret;
  if (pred.count(t) == 0) return {};
  ret.push_back(t);

  while (pred.count(t) != 0) ret.push_back(t = pred.at(t));
  std::reverse(ret.begin(), ret.end());

  return ret;
}

