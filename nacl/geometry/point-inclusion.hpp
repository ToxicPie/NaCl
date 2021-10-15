bool on_segment(pt a, pt b, pt p) {
  return cross(a, b, p) == 0 && dot((p - a), (p - b)) <= 0;
}
// p can be any polygon, but this is O(n)
bool inside(const vector<pt> &p, pt a) {
  int cnt = 0, n = p.size();
  for (int i = 0; i < n; i++) {
    pt l = p[i], r = p[(i + 1) % n];
    // change to return 0; for strict version
    if (on_segment(l, r, a)) return 1;
    cnt ^= ((a.y < l.y) - (a.y < r.y)) * cross(l, r, a) > 0;
  }
  return cnt;
}
