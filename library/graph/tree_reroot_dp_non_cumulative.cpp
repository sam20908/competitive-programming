/**
 * @brief Computes the answer for each vertex when they are the root of the tree.
 *        This is designed for non-cumulative transitions but uses more memory as a consequence.
 *
 * @param g Tree in adjacency list form.
 * @param init_dp Returns the initial state for a vertex. Called as `fn(ans0, u)`.
 * @param apply_dp Applies the child's state onto the current state. Called as `fn(dp&, const dp_child&, u)`.
 * @param merge_dp Merges a partial state onto the current state. Called as `fn(dp&, const dp_partial&)`.
 * @param ans0 Default state. Note that this may be different from the result of `vertex_initial_dp`.
 * @param root Initial root of the tree.
 * @param node_projection Projection to extract the vertex from an edge. Called as `fn(edge)`.
 * @return vector<T> List of answers where `ans[u]` is the answer for vertex `u`.
 */
 template <typename T, typename F = identity, typename E>
 vector<T> tree_reroot_dp(vector<vector<E>> &g, auto &&init_dp, auto &&apply_dp, auto &&merge_dp, T ans0, int root, F node_projection = {}) {
   int n = g.size();
   vector<T> dp(n, ans0), ans(n, ans0);
   auto dfs = [&](auto &self, int u, int p) -> void {
     init_dp(dp[u], u);
     for (auto &v : g[u])
       if (node_projection(v) != p) {
         self(self, node_projection(v), u);
         apply_dp(dp[u], dp[node_projection(v)], v);
       }
   };
   dfs(dfs, root, root);
   auto dfs2 = [&](auto &self, int u, int p, const T &pdp, const E &pe) -> void {
     init_dp(ans[u], u);
     if (u != p)
       apply_dp(ans[u], pdp, pe);
     int m = g[u].size();
     T ansl = ans0, ansr = ans0;
     vector<T> edp(m, ans[u]);
     for (int i = 1; i < m; i++) {
       if (int v = node_projection(g[u][i - 1]); v != p)
         apply_dp(ansl, dp[v], g[u][i - 1]);
       if (node_projection(g[u][i]) != p)
         merge_dp(edp[i], ansl);
     }
     for (int i = m - 2; i >= 0; i--) {
       if (int v = node_projection(g[u][i + 1]); v != p)
         apply_dp(ansr, dp[v], g[u][i + 1]);
       if (node_projection(g[u][i]) != p)
         merge_dp(edp[i], ansr);
     }
     for (int i = 0; i < m; i++)
       if (int v = node_projection(g[u][i]); v != p)
         self(self, v, u, edp[i], g[u][i]);
     for (auto &e : g[u])
       if (int v = node_projection(e); v != p)
         apply_dp(ans[u], dp[v], e);
   };
   dfs2(dfs2, root, root, ans0, {});
   return ans;
 }