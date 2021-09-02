ll hilbert(ll n, int x, int y) {
  ll res = 0;
  for (ll s = n / 2; s; s >>= 1) {
    int rx = !!(x & s), ry = !!(y & s);
    res += s * s * ((3 * rx) ^ ry);
    if (ry == 0) {
      if (rx == 1) x = s - 1 - x, y = s - 1 - y;
      swap(x, y);
    }
  }
  return res;
}
