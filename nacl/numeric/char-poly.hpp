/// source: Nyaan
/// https://github.com/NyaanNyaan/library

// calculate det(a - xI)
template <typename T>
vector<T> CharacteristicPolynomial(vector<vector<T>> a) {
  int N = a.size();

  for (int j = 0; j < N - 2; j++) {
    for (int i = j + 1; i < N; i++) {
      if (a[i][j] != 0) {
        swap(a[j + 1], a[i]);
        for (int k = 0; k < N; k++)
          swap(a[k][j + 1], a[k][i]);
        break;
      }
    }
    if (a[j + 1][j] != 0) {
      T inv = T(1) / a[j + 1][j];
      for (int i = j + 2; i < N; i++) {
        if (a[i][j] == 0) continue;
        T coe = inv * a[i][j];
        for (int l = j; l < N; l++)
          a[i][l] -= coe * a[j + 1][l];
        for (int k = 0; k < N; k++)
          a[k][j + 1] += coe * a[k][i];
      }
    }
  }

  vector<vector<T>> p(N + 1);
  p[0] = {T(1)};
  for (int i = 1; i <= N; i++) {
    p[i].resize(i + 1);
    for (int j = 0; j < i; j++) {
      p[i][j + 1] -= p[i - 1][j];
      p[i][j] += p[i - 1][j] * a[i - 1][i - 1];
    }
    T x = 1;
    for (int m = 1; m < i; m++) {
      x *= -a[i - m][i - m - 1];
      T coe = x * a[i - m - 1][i - 1];
      for (int j = 0; j < i - m; j++)
        p[i][j] += coe * p[i - m - 1][j];
    }
  }
  return p[N];
}
