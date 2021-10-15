/// source: Sergey Kopeliovich (burunduk30@gmail.com)

struct Edmonds {
  int n, T;
  vector<vector<int>> g;
  vector<int> pa, p, used, base;
  Edmonds(int n)
      : n(n), T(0), g(n), pa(n, -1), p(n), used(n),
        base(n) {}
  void add(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }
  int getBase(int i) {
    while (i != base[i])
      base[i] = base[base[i]], i = base[i];
    return i;
  }
  vector<int> toJoin;
  void mark_path(int v, int x, int b, vector<int> &path) {
    for (; getBase(v) != b; v = p[x]) {
      p[v] = x, x = pa[v];
      toJoin.push_back(v);
      toJoin.push_back(x);
      if (!used[x]) used[x] = ++T, path.push_back(x);
    }
  }
  bool go(int v) {
    for (int x : g[v]) {
      int b, bv = getBase(v), bx = getBase(x);
      if (bv == bx) {
        continue;
      } else if (used[x]) {
        vector<int> path;
        toJoin.clear();
        if (used[bx] < used[bv])
          mark_path(v, x, b = bx, path);
        else mark_path(x, v, b = bv, path);
        for (int z : toJoin) base[getBase(z)] = b;
        for (int z : path)
          if (go(z)) return 1;
      } else if (p[x] == -1) {
        p[x] = v;
        if (pa[x] == -1) {
          for (int y; x != -1; x = v)
            y = p[x], v = pa[y], pa[x] = y, pa[y] = x;
          return 1;
        }
        if (!used[pa[x]]) {
          used[pa[x]] = ++T;
          if (go(pa[x])) return 1;
        }
      }
    }
    return 0;
  }
  void init_dfs() {
    for (int i = 0; i < n; i++)
      used[i] = 0, p[i] = -1, base[i] = i;
  }
  bool dfs(int root) {
    used[root] = ++T;
    return go(root);
  }
  void match() {
    int ans = 0;
    for (int v = 0; v < n; v++)
      for (int x : g[v])
        if (pa[v] == -1 && pa[x] == -1) {
          pa[v] = x, pa[x] = v, ans++;
          break;
        }
    init_dfs();
    for (int i = 0; i < n; i++)
      if (pa[i] == -1 && dfs(i)) ans++, init_dfs();
    cout << ans * 2 << "\n";
    for (int i = 0; i < n; i++)
      if (pa[i] > i)
        cout << i + 1 << " " << pa[i] + 1 << "\n";
  }
};
