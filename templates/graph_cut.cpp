struct graph_cut {
  vector<int> disc, low, is_cut_vertex, is_cut_edge;
  graph_cut(vector<vector<pair<int, int>>> &g, int m)
      : disc(g.size()), low(g.size()), is_cut_vertex(g.size()), is_cut_edge(m) {
    int time = 0;
    auto f = [&](auto &self, int u, int p) -> int {
      int childs = 0;
      disc[u] = low[u] = ++time;
      for (auto [v, e] : g[u]) {
        if (v == p) continue;
        if (!disc[v]) {
          childs++;
          self(self, v, u);
          is_cut_vertex[u] = disc[u] <= low[v];
          is_cut_edge[e] = disc[u] < low[v];
          low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], disc[v]);
      }
      return childs;
    };
    for (int i = 0; i < g.size(); i++)
      if (!disc[i]) is_cut_vertex[i] = f(f, i, i) > 1;
  }
};