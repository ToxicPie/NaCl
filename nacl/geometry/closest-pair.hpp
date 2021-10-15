vector<pll> p; // sort by x first!
bool cmpy(const pll &a, const pll &b) const {
  return a.y < b.y;
}
ll sq(ll x) { return x * x; }
// returns (minimum dist)^2 in [l, r)
ll solve(int l, int r) {
  if (r - l <= 1) return 1e18;
  int m = (l + r) / 2;
  ll mid = p[m].x, d = min(solve(l, m), solve(m, r));
  auto pb = p.begin();
  inplace_merge(pb + l, pb + m, pb + r, cmpy);
  vector<pll> s;
  for (int i = l; i < r; i++)
    if (sq(p[i].x - mid) < d) s.push_back(p[i]);
  for (int i = 0; i < s.size(); i++)
    for (int j = i + 1;
         j < s.size() && sq(s[j].y - s[i].y) < d; j++)
      d = min(d, dis(s[i], s[j]));
  return d;
}
