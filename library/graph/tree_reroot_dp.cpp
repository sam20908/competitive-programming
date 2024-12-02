template <typename T, typename F = identity, typename E>
vector<T> tree_reroot_dp(vector<vector<E>> &g, auto &&apply, auto &&apply_dp, auto &&dp_combine, T ans0, int root, F node_projection = {}) {
  int n = g.size();
  vector<T> dp(n, ans0), ans(n, ans0);
  auto dfs = [&](auto &self, int u, int p) -> void {
    dp[u] = apply(dp[u], u);
    for (auto &v : g[u])
      if (node_projection(v) != p) {
        self(self, node_projection(v), u);
        dp[u] = apply_dp(dp[u], dp[node_projection(v)], v);
      }
  };
  dfs(dfs, root, root);
  auto dfs2 = [&](auto &self, int u, int p, T pdp, E pe) -> void {
    ans[u] = apply(ans[u], u);
    if (u != p)
      ans[u] = apply_dp(ans[u], pdp, pe);
    int m = g[u].size();
    T ansl = ans0, ansr = ans0;
    vector<T> edp(m, ans[u]);
    for (int i = 1; i < m; i++) {
      if (node_projection(g[u][i - 1]) != p)
        ansl = apply_dp(ansl, dp[node_projection(g[u][i - 1])], g[u][i - 1]);
      if (node_projection(g[u][i]) != p)
        edp[i] = dp_combine(edp[i], ansl);
    }
    for (int i = m - 2; i >= 0; i--) {
      if (node_projection(g[u][i + 1]) != p)
        ansr = apply_dp(ansr, dp[node_projection(g[u][i + 1])], g[u][i + 1]);
      if (node_projection(g[u][i]) != p)
        edp[i] = dp_combine(edp[i], ansr);
    }
    for (int i = 0; i < m; i++)
      if (node_projection(g[u][i]) != p)
        self(self, node_projection(g[u][i]), u, edp[i], g[u][i]);
    for (auto &v : g[u])
      if (node_projection(v) != p)
        ans[u] = apply_dp(ans[u], dp[node_projection(v)], v);
  };
  dfs2(dfs2, root, root, ans0, {});
  return ans;
}