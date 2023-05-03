// subtree of v is [in[v], out[v])
// top of heavy path of v is nxt[v]
void dfs1(int v) {
  sz[v] = 1;
  for (int u : child[v]) {
    par[v] = u;
    dfs1(u);
    sz[v] += sz[u];
    if (sz[u] > sz[child[v][0]]) { swap(u, child[v][0]); }
  }
}
void dfs2(int v) {
  in[v] = t++;
  for (int u : child[v]) {
    nxt[u] = (u == child[v][0] ? nxt[v] : u);
    dfs2(u);
  }
  out[v] = t;
}
int lca(int a, int b) {
  for (;; b = par[nxt[b]]) {
    if (in[b] < in[a]) swap(a, b);
    if (in[nxt[b]] <= in[a]) return a;
  }
}
