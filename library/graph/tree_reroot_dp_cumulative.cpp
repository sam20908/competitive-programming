template <typename T, typename F = identity, typename E>
vector<T> tree_reroot_dp(vector<vector<E>> &g, auto &&init_dp, auto &&apply_dp, auto &&remove_dp, T ans0, int root, F node_projection = {}) {
  int n = g.size();
  vector<T> dp(n, ans0), ans(n, ans0);
  auto dfs = [&](auto &self, int u, int p) -> void {
    init_dp(dp[u], u);
    for (auto &e : g[u])
      if (int v = node_projection(e); v != p) {
        self(self, v, u);
        apply_dp(dp[u], dp[v], e);
      }
  };
  dfs(dfs, root, root);
  auto dfs2 = [&](auto &self, int u, int p, const T &pdp, const E &pe) -> void {
    init_dp(ans[u], u);
    if (u != p)
      apply_dp(ans[u], pdp, pe);
    for (auto &e : g[u])
      if (int v = node_projection(e); v != p)
        apply_dp(ans[u], dp[v], e);
    for (auto &e : g[u])
      if (int v = node_projection(e); v != p) {
        remove_dp(ans[u], dp[v], e);
        self(self, v, u, ans[u], e);
        apply_dp(ans[u], dp[v], e);
      }
  };
  dfs2(dfs2, root, root, ans0, {});
  return ans;
}