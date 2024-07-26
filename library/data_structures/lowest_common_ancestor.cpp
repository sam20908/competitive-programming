struct lowest_common_ancestor {
  vector<vector<int>> dp;
  vector<int> in, out;
  lowest_common_ancestor(vector<vector<int>> &g, int root) : dp(__lg(g.size()) + 1, vector<int>(g.size())), in(g.size()), out(g.size()) {
    auto f = [&, time = 0](auto &self, int u, int p) mutable -> void {
      in[u] = ++time;
      dp[0][u] = p;
      for (int l = 1; l <= __lg(g.size()); l++)
        dp[l][u] = dp[l - 1][dp[l - 1][u]];
      for (int v : g[u])
        if (v != p)
          self(self, v, u);
      out[u] = ++time;
    };
    f(f, root, root);
  }
  bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v]; // if u is ancestor of v
  }
  int query(int u, int v) {
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;
    for (int l = __lg(in.size()); l >= 0; l--)
      if (!is_ancestor(dp[l][u], v))
        u = dp[l][u];
    return dp[0][u];
  }
};