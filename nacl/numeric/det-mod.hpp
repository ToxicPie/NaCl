#include "../math/number-theory/modular.hpp"

Mod det(vector<vector<Mod>> a) {
  int n = a.size();
  Mod ans = 1;
  for (int i = 0; i < n; i++) {
    int b = i;
    for (int j = i + 1; j < n; j++)
      if (a[j][i] != 0) {
        b = j;
        break;
      }
    if (i != b) swap(a[i], a[b]), ans = -ans;
    ans *= a[i][i];
    if (ans == 0) return 0;
    for (int j = i + 1; j < n; j++) {
      Mod v = a[j][i] / a[i][i];
      if (v != 0)
        for (int k = i + 1; k < n; k++)
          a[j][k] -= v * a[i][k];
    }
  }
  return ans;
}
