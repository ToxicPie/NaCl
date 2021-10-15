double det(vector<vector<double>> a) {
  int n = a.size();
  double ans = 1;
  for (int i = 0; i < n; i++) {
    int b = i;
    for (int j = i + 1; j < n; j++)
      if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
    if (i != b) swap(a[i], a[b]), ans = -ans;
    ans *= a[i][i];
    if (ans == 0) return 0;
    for (int j = i + 1; j < n; j++) {
      double v = a[j][i] / a[i][i];
      if (v != 0)
        for (int k = i + 1; k < n; k++)
          a[j][k] -= v * a[i][k];
    }
  }
  return ans;
}
