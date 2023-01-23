template <int MAX_HEIGHT = 100'000> struct lca_online {
  static inline int MAX_POWER = ceil(log2(MAX_HEIGHT));
  vector<vector<int>> up;
  vector<int> in, out;
  lca_online(vector<vector<int>> &adj, vector<int> &parent, int root)
      : up(parent.size(), vector<int>(MAX_POWER + 1, root)), in(parent.size()), out(parent.size()) {
    int time = 0;
    auto f = [&](auto &self, int cur, int prev = -1) -> void {
      in[cur] = ++time;
      up[cur][0] = parent[cur];
      for (int p = 1; p <= MAX_POWER; p++)
        up[cur][p] = up[cur][p - 1] == -1 ? -1 : up[up[cur][p - 1]][p - 1];
      for (int next : adj[cur]) {
        if (next != prev) {
          self(self, next, cur);
        }
      }
      out[cur] = ++time;
    };
    f(f, root);
  }
  bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v]; // if u is ancestor of v
  }
  int query(int u, int v) {
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;
    for (int p = MAX_POWER; p >= 0; p--)
      if (!is_ancestor(up[u][p], v))
        u = up[u][p];
    return up[u][0];
  }
};