auto angle_cmp = [](const pt &a, const pt &b) {
  auto btm = [](const pt &a) {
    return a.y < 0 || (a.y == 0 && a.x < 0);
  };
  return make_tuple(btm(a), a.y * b.x, abs2(a)) <
         make_tuple(btm(b), a.x * b.y, abs2(b));
};
void angular_sort(vector<pt> &p) {
  sort(p.begin(), p.end(), angle_cmp);
}
