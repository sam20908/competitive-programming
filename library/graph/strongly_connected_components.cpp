vector<vector<int>> strongly_connected_components(vector<vector<int>> &g) {
  vector<int> vis(g.size()), ord;
  vector<vector<int>> g2(g.size());
  for (int i = 0; i < g.size(); i++)
    for (int j : g[i])
      g2[j].push_back(i);
  ord.reserve(g.size());
  auto dfs1 = [&](auto &self, int u) -> void {
    vis[u] = true;
    for (int v : g[u])
      if (!vis[v])
        self(self, v);
    ord.push_back(u);
  };
  for (int i = 0; i < g.size(); i++)
    if (!vis[i])
      dfs1(dfs1, i);
  reverse(ord.begin(), ord.end());
  auto dfs2 = [&](auto &self, int u, vector<int> &comp) -> void {
    comp.push_back(u);
    vis[u] = false;
    for (int v : g2[u])
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