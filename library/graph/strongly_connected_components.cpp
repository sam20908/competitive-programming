vector<vector<int>> strongly_connected_components(int n, vector<vector<int>> &g) {
  vector<int> vis(n), ord;
  ord.reserve(n);
  auto dfs1 = [&](auto &self, int u) -> void {
    vis[u] = true;
    for (int v : g[u])
      if (!vis[v])
        self(self, v);
    ord.push_back(u);
  };
  for (int i = 0; i < n; i++)
    if (!vis[i])
      dfs1(dfs1, i);
  reverse(ord.begin(), ord.end());
  auto dfs2 = [&](auto &self, int u, vector<int> &comp) -> void {
    comp.push_back(u);
    vis[u] = false;
    for (int v : g[u])
      if (vis[v])
        self(self, v, comp);
  };
  vector<vector<int>> ans;
  for (int u : ord)
    if (vis[u]) {
      ans.push_back({});
      dfs2(dfs2, u, ans.back());
    }
  return ans;
}