// min dp[i] value and its i (smallest one)
pll get_dp(int n);
ll aliens(int n) {
  int l = 0, r = 1000000;
  while (l != r) {
    int m = (l + r) / 2;
    auto [f, s] = get_dp(m);
    if (s == n) return f - m * n;
    if (s < n) r = m;
    else l = m + 1;
  }
  return get_dp(--l).first - l * n;
}
