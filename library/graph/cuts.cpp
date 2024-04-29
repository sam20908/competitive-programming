pair<vector<int>, vector<int>> cuts(int n, int m, vector<vector<pair<int, int>>> &g) {
  vector<int> ans_vertex(n), ans_edge(m), disc(n), low(n);
  auto dfs = [&, time = 0] (auto &self, int u, int p) mutable -> int {
    int childs = 0;
    disc[u] = low[u] = ++time;
    for (auto [v, e] : g[u]) {
      if (v == p)
        continue;
      if (!disc[v]) {
        childs++;
        self(self, v, u);
        ans_vertex[u] = disc[u] <= low[v];
        ans_edge[e] = disc[u] < low[v];
        low[u] = min(low[u], low[v]);
      } else
        low[u] = min(low[u], disc[v]);
    }
    return childs;
  };
  for (int i = 0; i < g.size(); i++)
    if (!disc[i])
      ans_vertex[i] = dfs(dfs, i, -1);
  return {ans_vertex, ans_edge};
}