// returns the gcd of non-negative a, b
ull bin_gcd(ull a, ull b) {
  if (!a || !b) return a + b;
  int s = __builtin_ctzll(a | b);
  a >>= __builtin_ctzll(a);
  while (b) {
    if ((b >>= __builtin_ctzll(b)) < a) swap(a, b);
    b -= a;
  }
  return a << s;
}
