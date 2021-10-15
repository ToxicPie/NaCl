/// source: wleung_bvg
/// https://github.com/wesley-a-leung/Resources/blob/main/Content/C%2B%2B/graph/components/ThreeEdgeConnectedComponents.h

// requires a union-find data structure
struct ThreeEdgeCC {
  int V, ind;
  vector<int> id, pre, post, low, deg, path;
  vector<vector<int>> components;
  UnionFind uf;
  template <class Graph>
  void dfs(const Graph &G, int v, int prev) {
    pre[v] = ++ind;
    for (int w : G[v])
      if (w != v) {
        if (w == prev) {
          prev = -1;
          continue;
        }
        if (pre[w] != -1) {
          if (pre[w] < pre[v]) {
            deg[v]++;
            low[v] = min(low[v], pre[w]);
          } else {
            deg[v]--;
            int &u = path[v];
            for (; u != -1 && pre[u] <= pre[w] &&
                   pre[w] <= post[u];) {
              uf.join(v, u);
              deg[v] += deg[u];
              u = path[u];
            }
          }
          continue;
        }
        dfs(G, w, v);
        if (path[w] == -1 && deg[w] <= 1) {
          deg[v] += deg[w];
          low[v] = min(low[v], low[w]);
          continue;
        }
        if (deg[w] == 0) w = path[w];
        if (low[v] > low[w]) {
          low[v] = min(low[v], low[w]);
          swap(w, path[v]);
        }
        for (; w != -1; w = path[w]) {
          uf.join(v, w);
          deg[v] += deg[w];
        }
      }
    post[v] = ind;
  }
  template <class Graph>
  ThreeEdgeCC(const Graph &G)
      : V(G.size()), ind(-1), id(V, -1), pre(V, -1),
        post(V), low(V, INT_MAX), deg(V, 0), path(V, -1),
        uf(V) {
    for (int v = 0; v < V; v++)
      if (pre[v] == -1) dfs(G, v, -1);
    components.reserve(uf.cnt);
    for (int v = 0; v < V; v++)
      if (uf.find(v) == v) {
        id[v] = components.size();
        components.emplace_back(1, v);
        components.back().reserve(uf.getSize(v));
      }
    for (int v = 0; v < V; v++)
      if (id[v] == -1)
        components[id[v] = id[uf.find(v)]].push_back(v);
  }
};
