// before calling, do
// int top = max_element(c.begin(), c.end()) -
// c.begin();
// c.push_back(c[0]), c.push_back(c[1]);
pt left_tangent(const vector<pt> &c, int top, pt p) {
  int n = c.size() - 2;
  int ans = -1;
  do {
    if (cross(p, c[n], c[n + 1]) >= 0 &&
        (cross(p, c[top + 1], c[n]) > 0 ||
         cross(p, c[top], c[top + 1]) < 0))
      break;
    int l = top + 1, r = n + 1;
    while (l < r - 1) {
      int m = (l + r) / 2;
      if (cross(p, c[m - 1], c[m]) > 0 &&
          cross(p, c[top + 1], c[m]) > 0)
        l = m;
      else r = m;
    }
    ans = l;
  } while (false);
  do {
    if (cross(p, c[top], c[top + 1]) >= 0 &&
        (cross(p, c[1], c[top]) > 0 ||
         cross(p, c[0], c[1]) < 0))
      break;
    int l = 1, r = top + 1;
    while (l < r - 1) {
      int m = (l + r) / 2;
      if (cross(p, c[m - 1], c[m]) > 0 &&
          cross(p, c[1], c[m]) > 0)
        l = m;
      else r = m;
    }
    ans = l;
  } while (false);
  return c[ans] - p;
}
