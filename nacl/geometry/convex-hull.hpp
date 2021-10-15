// returns a convex hull in counterclockwise order
// for a non-strict one, change cross >= to >
vector<pt> convex_hull(vector<pt> p) {
  sort(ALL(p));
  if (p[0] == p.back()) return {p[0]};
  int n = p.size(), t = 0;
  vector<pt> h(n + 1);
  for (int _ = 2, s = 0; _--; s = --t, reverse(ALL(p)))
    for (pt i : p) {
      while (t > s + 1 && cross(i, h[t - 1], h[t - 2]) >= 0)
        t--;
      h[t++] = i;
    }
  return h.resize(t), h;
}
