#include "dinic.hpp"

int e[MAXN][MAXN];
int p[MAXN];
Dinic D; // original graph
void gomory_hu() {
  fill(p, p + n, 0);
  fill(e[0], e[n], INF);
  for (int s = 1; s < n; s++) {
    int t = p[s];
    Dinic F = D;
    int tmp = F.max_flow(s, t);
    for (int i = 1; i < s; i++)
      e[s][i] = e[i][s] = min(tmp, e[t][i]);
    for (int i = s + 1; i <= n; i++)
      if (p[i] == t && F.side[i]) p[i] = s;
  }
}
