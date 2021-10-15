// returns (e/f), where (a/b, c/d, e/f) are
// three consecutive terms in the order n farey sequence
// to start, call next_farey(n, 0, 1, 1, n)
pll next_farey(ll n, ll a, ll b, ll c, ll d) {
  ll p = (n + b) / d;
  return pll(p * c - a, p * d - b);
}
