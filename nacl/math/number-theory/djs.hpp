const ll N = 1000000;
// f, g, h multiplicative, h = f (dirichlet convolution) g
ll pre_g(ll n);
ll pre_h(ll n);
// preprocessed prefix sum of f
ll pre_f[N];
// prefix sum of multiplicative function f
ll solve_f(ll n) {
  static unordered_map<ll, ll> m;
  if (n < N) return pre_f[n];
  if (m.count(n)) return m[n];
  ll ans = pre_h(n);
  for (ll l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans -= (pre_g(r) - pre_g(l - 1)) * djs_f(n / l);
  }
  return m[n] = ans;
}
