/**
 * @brief Computes the answer for each vertex when they are the root of the tree.
 *        This is designed for cumulative transitions to save memory.
 *
 * @param g Tree in adjacency list form.
 * @param init_dp Returns the initial state for a vertex. Called as `fn(ans0, u)`.
 * @param apply_dp Applies the child's state onto the current state. Called as `fn(dp&, const dp_child&, u)`.
 * @param remove_dp Removes the child's state from the current state. Called as `fn(dp&, const dp_child&, u)`.
 * @param ans0 Default state. Note that this may be different from the result of `vertex_initial_dp`.
 * @param root Initial root of the tree.
 * @param node_projection Projection to extract the vertex from an edge. Called as `fn(edge)`.
 * @return vector<T> List of answers where `ans[u]` is the answer for vertex `u`.
 */
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