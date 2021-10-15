/// source: 2021 YCPC

#include "../ds/pbds.hpp"
#include "point.hpp"

using Double = __float128;
using Point = pt<Double, Double>;

int n, m;
vector<Point> poly;
vector<Point> query;
vector<int> ans;

struct Segment {
  Point a, b;
  int id;
};
vector<Segment> segs;

Double Xnow;
inline Double get_y(const Segment &u, Double xnow = Xnow) {
  const Point &a = u.a;
  const Point &b = u.b;
  return (a.y * (b.x - xnow) + b.y * (xnow - a.x)) /
         (b.x - a.x);
}
bool operator<(Segment u, Segment v) {
  Double yu = get_y(u);
  Double yv = get_y(v);
  if (yu != yv) return yu < yv;
  return u.id < v.id;
}
ordered_map<Segment> st;

struct Event {
  int type; // +1 insert seg, -1 remove seg, 0 query
  Double x, y;
  int id;
};
bool operator<(Event a, Event b) {
  if (a.x != b.x) return a.x < b.x;
  if (a.type != b.type) return a.type < b.type;
  return a.y < b.y;
}
vector<Event> events;

void solve() {
  set<Double> xs;
  set<Point> ps;
  for (int i = 0; i < n; i++) {
    xs.insert(poly[i].x);
    ps.insert(poly[i]);
  }
  for (int i = 0; i < n; i++) {
    Segment s{poly[i], poly[(i + 1) % n], i};
    if (s.a.x > s.b.x ||
        (s.a.x == s.b.x && s.a.y > s.b.y)) {
      swap(s.a, s.b);
    }
    segs.push_back(s);

    if (s.a.x != s.b.x) {
      events.push_back({+1, s.a.x + 0.2, s.a.y, i});
      events.push_back({-1, s.b.x - 0.2, s.b.y, i});
    }
  }
  for (int i = 0; i < m; i++) {
    events.push_back({0, query[i].x, query[i].y, i});
  }
  sort(events.begin(), events.end());
  int cnt = 0;
  for (Event e : events) {
    int i = e.id;
    Xnow = e.x;
    if (e.type == 0) {
      Double x = e.x;
      Double y = e.y;
      Segment tmp = {{x - 1, y}, {x + 1, y}, -1};
      auto it = st.lower_bound(tmp);

      if (ps.count(query[i]) > 0) {
        ans[i] = 0;
      } else if (xs.count(x) > 0) {
        ans[i] = -2;
      } else if (it != st.end() &&
                 get_y(*it) == get_y(tmp)) {
        ans[i] = 0;
      } else if (it != st.begin() &&
                 get_y(*prev(it)) == get_y(tmp)) {
        ans[i] = 0;
      } else {
        int rk = st.order_of_key(tmp);
        if (rk % 2 == 1) {
          ans[i] = 1;
        } else {
          ans[i] = -1;
        }
      }
    } else if (e.type == 1) {
      st.insert(segs[i]);
      assert((int)st.size() == ++cnt);
    } else if (e.type == -1) {
      st.erase(segs[i]);
      assert((int)st.size() == --cnt);
    }
  }
}
