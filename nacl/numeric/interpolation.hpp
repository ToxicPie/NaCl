/// source: KACTL

// returns a, such that a[0]x^0 + a[1]x^1 + a[2]x^2 + ...
// passes through the given points
typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) {
  vd res(n), temp(n);
  rep(k, 0, n - 1) rep(i, k + 1, n) y[i] =
  (y[i] - y[k]) / (x[i] - x[k]);
  double last = 0;
  temp[0] = 1;
  rep(k, 0, n) rep(i, 0, n) {
    res[i] += y[k] * temp[i];
    swap(last, temp[i]);
    temp[i] -= last * x[k];
  }
  return res;
}
