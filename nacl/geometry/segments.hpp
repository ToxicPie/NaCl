// for non-collinear ABCD, if segments AB and CD intersect
bool intersects(pt a, pt b, pt c, pt d) {
  if (cross(b, c, a) * cross(b, d, a) > 0) return false;
  if (cross(d, a, c) * cross(d, b, c) > 0) return false;
  return true;
}
// the intersection point of lines AB and CD
pt intersect(pt a, pt b, pt c, pt d) {
  auto x = cross(b, c, a), y = cross(b, d, a);
  if (x == y) {
    // if(abs(x, y) < 1e-8) {
    // is parallel
  } else {
    return d * (x / (x - y)) - c * (y / (x - y));
  }
}
