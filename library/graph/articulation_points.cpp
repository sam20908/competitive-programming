/**
 * @brief Computes the articulation points of a graph
 *
 * @param g Graph in adjacency list form
 * @return List of articulation points
 */
vector<int> articulation_points(vector<vector<int>> &g) {
  int n = g.size();
  vector<int> in(n, -1), low(n, -1), ans;
  auto dfs = [&, timer = 0](auto &self, int v, int p = -1) mutable -> void {
    in[v] = low[v] = timer++;
    int children = 0;
    for (int to : g[v]) {
      if (to == p)
        continue;
      if (in[to] != -1) {
        low[v] = min(low[v], in[to]);
      } else {
        self(self, to, v);
        low[v] = min(low[v], low[to]);
        if (low[to] >= in[v] && p != -1)
          ans.push_back(v);
        ++children;
      }
    }
    if (p == -1 && children > 1)
      ans.push_back(v);
  };
  for (int i = 0; i < n; ++i)
    if (in[i] == -1)
      dfs(dfs, i);
  return ans;
};