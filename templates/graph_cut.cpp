struct graph_cut {
  vector<int> disc, low, is_cut_vertex, is_cut_edge;
  graph_cut(vector<vector<pair<int, int>>> &adj, int edges)
      : disc(adj.size()), low(adj.size()), is_cut_vertex(adj.size()), is_cut_edge(edges) {
    int time = 0;
    auto f = [&](auto &self, int cur, int prev) -> int {
      int childrens = 0;
      disc[cur] = low[cur] = ++time;
      for (auto [next, edge_id] : adj[cur]) {
        if (next == prev) continue;
        if (!disc[next]) {
          childrens++;
          self(self, next, cur);
          is_cut_vertex[cur] = disc[cur] <= low[next];
          is_cut_edge[edge_id] = disc[cur] < low[next];
          low[cur] = min(low[cur], low[next]);
        } else low[cur] = min(low[cur], disc[next]);
      }
      return childrens;
    };
    for (int i = 0; i < adj.size(); i++)
      if (!disc[i]) is_cut_vertex[i] = f(f, i, i) > 1;
  }
};